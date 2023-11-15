/*
 * @lc app=leetcode.cn id=1114 lang=cpp
 *
 * [1114] 按序打印
 */

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <stdio.h>

#include <functional>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <atomic>

using namespace std;

// @lc code=start
class Foo {
 private:
  atomic<unsigned int> should_run_idx;
  mutex m;
  condition_variable cv;

 public:
  Foo() {
    should_run_idx = 0;
  }

  void do_work(function<void()> print, function<bool ()> check) {
    unique_lock<mutex> lock(m);
    cv.wait(lock, [&] { return check(); });

    should_run_idx = (should_run_idx + 1) % 3;
    print();
    cv.notify_all();
  }

  void first(function<void()> printFirst) {
    // printFirst() outputs "first". Do not change or remove this line.
    // printFirst();
    do_work(printFirst, [&] { return should_run_idx == 0; });
  }

  void second(function<void()> printSecond) {
    // printSecond() outputs "second". Do not change or remove this line.
    // printSecond();
    do_work(printSecond, [&] { return should_run_idx == 1; });
  }

  void third(function<void()> printThird) {
    // printThird() outputs "third". Do not change or remove this line.
    // printThird();
    do_work(printThird, [&] { return should_run_idx == 2; });
  }
};
// @lc code=end

void first() { printf("first"); }
void second() { printf("second"); }
void third() { printf("third"); }

int main() {
  vector<int> nums = {1, 2, 3};
  Foo foo;
  unordered_map<int, function<void(function<void()>)>> func_map = {
      {1, bind(&Foo::first, &foo, placeholders::_1)},
      {2, bind(&Foo::second, &foo, placeholders::_1)},
      {3, bind(&Foo::third, &foo, placeholders::_1)}};

  thread t1(func_map[nums[0]], first);
  thread t2(func_map[nums[1]], second);
  thread t3(func_map[nums[2]], third);
  // thread t1(&Foo::first, &foo, first);
  // thread t2(&Foo::second, &foo, second);
  // thread t3(&Foo::third, &foo, third);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}
