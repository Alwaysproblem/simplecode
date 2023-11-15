/*
 * @lc app=leetcode.cn id=1116 lang=cpp
 *
 * [1116] 打印零与奇偶数
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
// https://zhuanlan.zhihu.com/p/532340603
// @lc code=start
class ZeroEvenOdd {
 private:
  int n;
  atomic<int> flag;

 public:
  ZeroEvenOdd(int n) {
    this->n = n;
    flag = 0;
  }

  // printNumber(x) outputs "x", where x is an integer.
  void zero(function<void(int)> printNumber) {
    for (int i = 1; i <= n; i++) {
      while (flag != 0) {
        this_thread::yield();
      }
      printNumber(0);
      flag = i % 2 == 0 ? 2 : 1;
    }
  }

  void even(function<void(int)> printNumber) {
    for (int i = 2; i <= n; i += 2) {
      while (flag != 2) {
        this_thread::yield();
      }
      printNumber(i);
      flag = 0;
    }
  }

  void odd(function<void(int)> printNumber) {
    for (int i = 1; i <= n; i += 2) {
      while (flag != 1) {
        this_thread::yield();
      }
      printNumber(i);
      flag = 0;
    }
  }
};
// @lc code=end

void printNumber(int x) { printf("%d", x); }

int main() {
  ZeroEvenOdd foo(5);

  thread t1(&ZeroEvenOdd::zero, &foo, printNumber);
  thread t2(&ZeroEvenOdd::even, &foo, printNumber);
  thread t3(&ZeroEvenOdd::odd, &foo, printNumber);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}
