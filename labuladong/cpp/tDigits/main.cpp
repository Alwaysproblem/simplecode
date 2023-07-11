#include <fmt/format.h>
#include <fmt/ranges.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

// using namespace std;

class Bin {
 public:
  double avg;
  int size;

  Bin(double _avg, int _size = 1) : avg(_avg), size(_size) {}

  // Override the '+' operator to implement merging two bins
  Bin operator+(const Bin& other) const {
    double weight = avg * size + other.avg * other.size;
    int size = this->size + other.size;
    return Bin(weight / size, size);
  }

  // Override the '+=' operator to implement merging two bins
  Bin& operator+=(const Bin& other) {
    double weight = avg * size + other.avg * other.size;
    this->size += other.size;
    this->avg = weight / this->size;
    return *this;
  }

};

void printBins(std::vector<Bin>& bins) {
  fmt::print("bins: [");
  for (auto bin : bins) {
    fmt::print("avg: {}, ", bin.avg, bin.size);
  }
  fmt::print("]\n");
};

class TDigest {
 public:
  std::vector<Bin> bins;
  int delta;

  TDigest(std::vector<Bin> _bins = {}, int _delta = 10)
      : bins(_bins), delta(_delta) {
    if (!_bins.empty()) {
      merge_to_bins(_bins);
      self_compress();
    }
    bins.reserve(delta);
  }

  int get_elements_count() const {
    int count = 0;
    for (const auto& bin : bins) {
      count += bin.size;
    }
    return count;
  }

  // Add one element by converting it to a single-element t-digest then
  // concatenating with this one.
  void append(double value) {
    merge_to_bins({Bin(value)});
    self_compress();
  }

  double get_quantile(double qid) const {
    auto n = get_elements_count();
    auto idx = qid * n;

    auto max_idx = bins[0].size / 2.0;

    if (idx < max_idx) {
      return bins[0].avg;
    }

    for (int i = 0; i < bins.size() - 1; ++i) {
      auto& b = bins[i];
      auto& b_next = bins[i + 1];

      auto interval_length = (b.size + b_next.size) / 2.0;
      if (idx <= max_idx + interval_length) {
        auto k = (idx - max_idx) / interval_length;
        return b.avg * (1 - k) + b_next.avg * k;
      }

      max_idx += interval_length;
    }

    return bins.back().avg;
  }

 private:
  double get_potential(double qid) const {
    return delta * asin(2 * qid - 1) / (2 * M_PI);
  }

  std::vector<Bin> merge_bins(const std::vector<Bin>& xs,
                              const std::vector<Bin>& ys) const {
    std::vector<Bin> merged;
    int i = 0, j = 0;
    while (i < xs.size() && j < ys.size()) {
      if (xs[i].avg <= ys[j].avg) {
        merged.push_back(xs[i]);
        ++i;
      } else {
        merged.push_back(ys[j]);
        ++j;
      }
    }

    while (i < xs.size()) {
      merged.push_back(xs[i]);
      ++i;
    }

    while (j < ys.size()) {
      merged.push_back(ys[j]);
      ++j;
    }

    return merged;
  }

  std::vector<Bin> compress(const std::vector<Bin>& xs) const {
    if (xs.empty()) {
      return xs;
    }

    int n = 0;
    for (const auto& x : xs) {
      n += x.size;
    }

    std::vector<Bin> ys{xs[0]};
    auto min_potential = get_potential(0);
    auto total = xs[0].size;

    for (int i = 1; i < xs.size(); ++i) {
      const auto& x = xs[i];
      auto next_qid = 1.0 * (total + x.size) / n;

      if (get_potential(next_qid) - min_potential <= 1) {
        ys.back() = ys.back() + x;
      } else {
        ys.push_back(x);
        min_potential = get_potential(1.0 * total / n);
      }

      total += x.size;
    }

    return ys;
  }

  void merge_to_bins(const std::vector<Bin>& ys) {

    std::vector<Bin> merged;
    merged.reserve(delta);
    int i = 0, j = 0;
    while (i < bins.size() && j < ys.size()) {
      if (bins[i].avg <= ys[j].avg) {
        merged.push_back(std::move(bins[i]));
        ++i;
      } else {
        merged.push_back(std::move(ys[j]));
        ++j;
      }
    }

    while (i < bins.size()) {
      merged.push_back(std::move(bins[i]));
      ++i;
    }

    while (j < ys.size()) {
      merged.push_back(std::move(ys[j]));
      ++j;
    }
    bins.swap(merged);
    return;
  }

  void self_compress() {
    if (bins.empty()) {
      return;
    }

    int n = 0;
    for (const auto& x : bins) {
      n += x.size;
    }

    std::vector<Bin> ys{bins[0]};
    ys.reserve(delta);
    auto min_potential = get_potential(0);
    auto total = bins[0].size;

    for (int i = 1; i < bins.size(); ++i) {
      auto next_qid = 1.0 * (total + bins[i].size) / n;
      if (get_potential(next_qid) - min_potential <= 1) {
        ys.back() += bins[i];
      } else {
        ys.push_back(std::move(bins[i]));
        min_potential = get_potential(1.0 * total / n);
      }
      total += bins[i].size;
    }

    bins.swap(ys);
  }
};

int main() {
  // Create a random number generator engine
  std::random_device rd;
  // std::mt19937 gen(0);
  std::mt19937 gen(rd());

  // Define a distribution for the generator
  // std::uniform_int_distribution<> dis(1, 10);
  std::normal_distribution<> dis(0, 1);

  // Generate a random number
  // int random_number = dis(gen);
  float random_number = dis(gen);
//   const long long iters = 10;
  const long long iters = 10000;
  const float p = 0.9;

  std::vector<double> data;
  data.reserve(iters);
  for (long long i = 0; i < iters; ++i) {
    data.push_back(dis(gen));
  }

  TDigest tdigest({}, 100);
  auto start_time = std::chrono::high_resolution_clock::now();

  for (auto d : data) {
    tdigest.append(d);
  }
  auto end_time = std::chrono::high_resolution_clock::now();

  // Print the result
  fmt::print("P90 number: {}\n", tdigest.get_quantile(p));

  // Calculate the elapsed time
  auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(
      end_time - start_time);

  std::sort(data.begin(), data.end());
  int idx = int(iters * p);
  fmt::print("correct P90 number: {}\n", data[idx]);

  fmt::print("the related absolute error: {}% \n", std::abs(data[idx] - tdigest.get_quantile(p)) * 100 / data[idx] );

  // Print the result
  fmt::print("Elapsed time: {} microseconds\n", elapsed_time.count());
  fmt::print("Elapsed time: {} microseconds per append\n",
             float(elapsed_time.count()) / iters);

  return 0;
}
