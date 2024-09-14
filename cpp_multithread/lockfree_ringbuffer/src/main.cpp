#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <ratio>
#include <thread>

#include "profiler.h"

void task(std::string msg, int intervals, rperf::Channel& c) {
  for (int i = 0; i < 1050; i++) {
    std::string t_msg = msg + " " + std::to_string(i) + " - " + "interval " +
                        std::to_string(intervals);
    rperf::TracePoint p(&c, t_msg);
    // auto p = std::make_unique<rperf::TracePoint>(c, t_msg);
    std::cout << msg << " says: "
              << "fuck you " << msg << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(intervals));
  }
}

int main(int argc, const char *argv[]) {
  rperf::Channel c("CPU", 1024 * 1024, 1024 * 1024);
  std::chrono::time_point<std::chrono::system_clock> start, end;

  // auto c = std::make_shared<rperf::Channel>("CPU", 1024, 1024 * 1024);
  std::thread t1(task, "Thread 1", 15, std::ref(c));
  std::thread t2(task, "Thread 2", 17, std::ref(c));
  std::thread t3(task, "Thread 3", 25, std::ref(c));
  std::thread t4(task, "Thread 4", 17, std::ref(c));

  // start = std::chrono::system_clock::now();

  // for (int i = 0; i < 1000; i++) {
  //   rperf::TracePoint p(&c, "main " + std::to_string(i));
  //   std::cout << "main says: "
  //             << "fuck you Threads" << std::endl;
  //   std::this_thread::sleep_for(std::chrono::milliseconds(5));
  // }

  // end = std::chrono::system_clock::now();
  // std::chrono::duration<double, std::milli> duration_time =
  //     end - start;
  // std::cout << "duration: " << duration_time.count() << " ms";

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  return 0;
}

// 30776.7 with LOG
// 30786.2 without LOG
// 30771.8 without API

// DEBUG cmake
// 5585.92 with log
// 6196.68 without log
// 6173.81 without log api

// release cmake
// 5665.76 with log
// 6185.64 without log
// 6142.28 without log api
