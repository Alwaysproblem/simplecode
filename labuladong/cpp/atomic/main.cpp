// #include <fmt/format.h>
// #include <fmt/ranges.h>

// #include <iostream>
// #include <unordered_map>
// #include <std::vector>

// #include <atomic>
// #include <thread>

// // using namespace std;

// std::atomic<int> counter(0);

// // Wait-free algorithm
// void waitFreeIncrement() {
//     int value = counter.load();
//     while (!counter.compare_exchange_weak(value, value + 1)) {
//         value = counter.load();
//     }
// }

// // Lock-free algorithm
// void lockFreeIncrement() {
//     counter.fetch_add(1);
// }

// int main() {
//     std::thread t1(waitFreeIncrement);
//     std::thread t2(lockFreeIncrement);

//     t1.join();
//     t2.join();

//     std::cout << "Counter value: " << counter << std::endl;

//     return 0;
// }

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>

std::atomic<bool> x{false}, y{false};

void thread1() {
    x.store(true, std::memory_order_relaxed); // (1)
    y.store(true, std::memory_order_relaxed); // (2)
}

void thread2() {
    while (!y.load(std::memory_order_relaxed)); // (3)
    assert(x.load()); // (4)
}

// std::atomic<int> z{0};

// void read_x_then_y() {
//   while (!x.load(std::memory_order_seq_cst))
//     ;                                          // (3)
//   if (y.load(std::memory_order_seq_cst)) ++z;  // (4)
// }

// void read_y_then_x() {
//   while (!y.load(std::memory_order_seq_cst))
//     ;                                          // (5)
//   if (x.load(std::memory_order_seq_cst)) ++z;  // (6)
// }

int main() {
  std::thread a(thread1), b(thread2);
  // std::thread a(thread1), b(thread2), c(read_x_then_y), d(read_y_then_x);
  a.join(), b.join();
  // a.join(), b.join(), c.join(), d.join();
  // std::cout << z.load() << std::endl;  // (7)
}
