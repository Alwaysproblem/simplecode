/*
 * @lc app=leetcode.cn id=1115 lang=cpp
 *
 * [1115] 交替打印 FooBar
 */

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <stdio.h>

#include <atomic>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
// class FooBar {
// private:
//     int n;
//     atomic<int> run_flag;
//     condition_variable cv;
//     mutex m;

// public:
//     FooBar(int n) {
//         this->n = n;
//         run_flag = 1;
//     }

//     void foo(function<void()> printFoo) {
//         unique_lock<mutex> lock(m);
//         for (int i = 0; i < n; i++) {
//           cv.wait(lock, [&] { return run_flag == 1; });
//           // printFoo() outputs "foo". Do not change or remove this line.
//           run_flag = 2;
//           printFoo();
//           cv.notify_all();
//         }
//     }

//     void bar(function<void()> printBar) {
//         unique_lock<mutex> lock(m);
//         for (int i = 0; i < n; i++) {
//           cv.wait(lock, [&] { return run_flag == 2; });
//           run_flag = 1;
//           // printBar() outputs "bar". Do not change or remove this line.
//           printBar();
//           cv.notify_all();
//         }
//     }

// };

class FooBar {
 private:
  int n;
  promise<void> p1;
  promise<void> p2;

 public:
  FooBar(int n) {
    this->n = n;
    p1.set_value();
  }

  void foo(function<void()> printFoo) {
    for (int i = 0; i < n; i++) {
      p1.get_future().get();
      p1 = promise<void>();
      // printFoo() outputs "foo". Do not change or remove this line.
      printFoo();
      p2.set_value();
    }
  }

  void bar(function<void()> printBar) {
    for (int i = 0; i < n; i++) {
      p2.get_future().get();
      p2 = promise<void>();
      // printBar() outputs "bar". Do not change or remove this line.
      printBar();
      p1.set_value();
    }
  }
};
// @lc code=end

void foo() { printf("foo"); }
void bar() { printf("bar"); }

int main() {
  const int n = 2;
  FooBar fb(n);

  thread t1(&FooBar::foo, &fb, foo);
  thread t2(&FooBar::bar, &fb, bar);

  t1.join();
  t2.join();

  return 0;
}
