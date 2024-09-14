//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#ifndef CMAKE_DIVISION_H
#define CMAKE_DIVISION_H

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <atomic>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <mutex>
#include <ostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace rperf {

template <typename T>
class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity)
      : buffer_(capacity), capacity_(capacity) {
    assert(capacity >= 1 && "Capacity must be at least 1");
    for (size_t i = 0; i < capacity_; ++i) {
      buffer_[i].sequence.store(i, std::memory_order_relaxed);
    }
    head_.store(0, std::memory_order_relaxed);
    tail_.store(0, std::memory_order_relaxed);
  }

  ~RingBuffer() = default;

  bool push(const T& data) {
    Cell* cell;
    size_t pos = tail_.load(std::memory_order_relaxed);

    while (true) {
      cell = &buffer_[pos % capacity_];
      size_t seq = cell->sequence.load(std::memory_order_acquire);
      intptr_t dif = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos);

      if (dif == 0) {
        if (tail_.compare_exchange_weak(pos, pos + 1,
                                        std::memory_order_relaxed)) {
          cell->data = data;
          cell->sequence.store(pos + 1, std::memory_order_release);
          return true;
        } else {
          pos = tail_.load(std::memory_order_relaxed);
        }
      } else if (dif < 0) {
        // 队列已满
        return false;
      } else {
        pos = tail_.load(std::memory_order_relaxed);
      }
    }
  }

  bool pop(T& data) {
    Cell* cell;
    size_t pos = head_.load(std::memory_order_relaxed);
    while (true) {
      cell = &buffer_[pos % capacity_];
      size_t seq = cell->sequence.load(std::memory_order_acquire);
      intptr_t dif =
          static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos + 1);

      if (dif == 0) {
        if (head_.compare_exchange_weak(pos, pos + 1,
                                        std::memory_order_relaxed)) {
          data = cell->data;
          cell->sequence.store(pos + capacity_, std::memory_order_release);
          return true;
        } else {
          pos = head_.load(std::memory_order_relaxed);
        }
      } else if (dif < 0) {
        // 队列为空
        return false;
      } else {
        pos = head_.load(std::memory_order_relaxed);
      }
    }
  }

 private:
  struct Cell {
    std::atomic<size_t> sequence;
    T data;
  };

  std::vector<Cell> buffer_;
  const size_t capacity_;
  std::atomic<size_t> head_;
  std::atomic<size_t> tail_;
};

class HighPerformanceWriter {
 public:
  HighPerformanceWriter(const char* filename, size_t initial_size)
      : size_(initial_size), offset_(0) {
    fd_ = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd_ == -1) {
      throw std::runtime_error("Failed to open file");
    }

    // 预先设置文件大小
    if (ftruncate(fd_, size_) == -1) {
      close(fd_);
      throw std::runtime_error("Failed to set file size");
    }

    // 内存映射文件
    data_ = static_cast<char*>(
        mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0));
    if (data_ == MAP_FAILED) {
      close(fd_);
      throw std::runtime_error("Failed to mmap file");
    }
  }

  // 禁用拷贝和移动操作
  HighPerformanceWriter(const HighPerformanceWriter&) = delete;
  HighPerformanceWriter(HighPerformanceWriter&&) = delete;
  HighPerformanceWriter& operator=(const HighPerformanceWriter&) = delete;
  HighPerformanceWriter& operator=(HighPerformanceWriter&&) = delete;

  ~HighPerformanceWriter() {
    if (data_) {
      // 确保数据写入磁盘
      msync(data_, offset_, MS_SYNC);
      munmap(data_, size_);
      data_ = nullptr;
    }
    if (fd_ != -1) {
      close(fd_);
      fd_ = -1;
    }
  }

  void log(std::string_view message) {
    std::lock_guard<std::mutex> lock(mutex_);  // 保证线程安全
    size_t total_size = message.size() + 1;    // 包含换行符
    if (offset_ + total_size > size_) {
      resize(std::max(size_ * 2, offset_ + total_size));
    }
    std::memcpy(data_ + offset_, message.data(), message.size());
    offset_ += message.size();
    data_[offset_++] = '\n';
  }

 private:
  void resize(size_t new_size) {
    if (new_size <= size_) {
      return;  // 无需调整
    }

    // 同步数据并解除旧的内存映射
    if (msync(data_, offset_, MS_SYNC) == -1) {
      throw std::runtime_error("Failed to msync file");
    }
    if (munmap(data_, size_) == -1) {
      throw std::runtime_error("Failed to munmap file");
    }

    // 扩展文件大小
    if (ftruncate(fd_, new_size) == -1) {
      throw std::runtime_error("Failed to extend file size");
    }

    // 重新映射文件
    data_ = static_cast<char*>(
        mmap(nullptr, new_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0));
    if (data_ == MAP_FAILED) {
      throw std::runtime_error("Failed to remap file");
    }

    size_ = new_size;
  }

  int fd_;
  size_t size_;
  size_t offset_;
  char* data_;
  std::mutex mutex_;  // 用于线程同步
};

class CPUProfilerLogger {
 public:
  CPUProfilerLogger(std::string& log_dir, size_t ring_buffer_size = 1024,
                    size_t initialize_size = 1024 * 1024)
      : stop(false),
        file_writer((log_dir + "/cpu_runtime.txt").c_str(), initialize_size),
        ring_buffer(ring_buffer_size) {
    logging_thread = std::thread(&CPUProfilerLogger::process_logs, this);
  }

  CPUProfilerLogger(const CPUProfilerLogger&) = delete;
  CPUProfilerLogger& operator=(const CPUProfilerLogger&) = delete;

  ~CPUProfilerLogger() {
    stop = true;
    if (logging_thread.joinable()) {
      logging_thread.join();
    }
  }

  void log(const std::string message) { ring_buffer.push(message); }

 private:
  void process_logs() {
    std::string message;
    while (!stop) {
      if (ring_buffer.pop(message)) {
        file_writer.log(message);
      }
      std::this_thread::sleep_for(std::chrono::microseconds(5));
    }
    // Flush remaining logs before stopping
    while (ring_buffer.pop(message)) {
      file_writer.log(message);
    }
  }

  RingBuffer<std::string> ring_buffer;
  std::thread logging_thread;
  std::condition_variable cond_var;
  std::mutex mutex;
  std::atomic<bool> stop;
  HighPerformanceWriter file_writer;
};

class Channel {
 public:
  explicit Channel(std::string channel_name, size_t ring_buffer_size = 1024,
                   size_t initialize_size = 1024 * 1024)
      : channel_name_(channel_name) {
    const char* env_var = std::getenv("TVM_RCAR_PROFILE_CPU");
    log_env_is_set = env_var != nullptr;
    if (log_env_is_set) {
      log_dir = std::string(env_var);
      std::__fs::filesystem::path log_dir_path(log_dir);
      if (!std::__fs::filesystem::exists(log_dir)) {
        std::__fs::filesystem::create_directory(log_dir);
      }
      logger = std::make_shared<CPUProfilerLogger>(log_dir, ring_buffer_size,
                                                   initialize_size);
    }
  }

  bool is_enabled() const { return log_env_is_set; }
  std::string get_log_dir() const { return log_dir; }
  std::string get_channel_name() const { return channel_name_; }
  // CPUProfilerLogger& get_logger() { return logger; }
  std::shared_ptr<CPUProfilerLogger> get_logger() { return logger; }

  ~Channel() = default;

 private:
  std::string channel_name_;
  bool log_env_is_set;
  std::string log_dir;
  // CPUProfilerLogger logger;
  std::shared_ptr<CPUProfilerLogger> logger;
};

class TracePoint {
 public:
  enum class Status { START, STOP, CAPTURE };
  TracePoint() = delete;
  TracePoint(Channel* channel, std::string trace_label)
      : m_channel(channel), trace_label(trace_label), running(Status::START) {
    start_time = std::chrono::high_resolution_clock::now();
    end_time = std::chrono::high_resolution_clock::now();
    start_time_ms =
        std::chrono::duration<double, std::milli>(start_time.time_since_epoch())
            .count();
    end_time_ms =
        std::chrono::duration<double, std::milli>(start_time.time_since_epoch())
            .count();
    duration_time = end_time - start_time;
  };

  ~TracePoint() {
    stop();
    if (m_channel->is_enabled()) {
      capture();
    }
    running = Status::STOP;
  };

  void start() {
    running = Status::START;
    start_time = std::chrono::high_resolution_clock::now();
    start_time_ms =
        std::chrono::duration<double, std::milli>(start_time.time_since_epoch())
            .count();
  }

  void stop() {
    if (running == Status::START) {
      running = Status::CAPTURE;
      end_time = std::chrono::high_resolution_clock::now();
      end_time_ms =
          std::chrono::duration<double, std::milli>(end_time.time_since_epoch())
              .count();
      duration_time = end_time - start_time;
    }
  }

  std::string capture();

 private:
  Channel* m_channel;
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
  std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
  double start_time_ms;
  double end_time_ms;
  std::chrono::duration<double, std::milli> duration_time;
  std::string trace_label;
  Status running;
};
}  // namespace rperf

#endif  // CMAKE_DIVISION_H
