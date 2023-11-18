/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 * title: sliding-window-maximum
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <deque>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
template <typename T>
class MonotonicQueue {
 public:
  deque<T> q;
  MonotonicQueue() : q(){};
  ~MonotonicQueue() = default;
  // void Print() const { fmt::print("{}\n", q); }
  void push(T& elem) {
    while (!q.empty() && q.back() < elem) q.pop_back();
    q.push_back(elem);
  }
  void pop(T& elem) {
    if (q.front() == elem) q.pop_front();
  }
  T& max() { return q.front(); }
};

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    MonotonicQueue<int> window;
    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
      if (i < k - 1) {
        window.push(nums[i]);
      } else {
        // window.Print();
        window.push(nums[i]);
        res.push_back(window.max());
        window.pop(nums[i - k + 1]);
      }
    }
    // fmt::print("{}\n", res);
    return res;
  }
};
// @lc code=end

int main() {
  vector<int> nums = {-7, -8, 7, 5, 7, 1, 6, 0};
  int k = 4;
  Solution sol;
  vector<int> v = sol.maxSlidingWindow(nums, k);
  fmt::print("{}\n", v);
  return 0;
}
