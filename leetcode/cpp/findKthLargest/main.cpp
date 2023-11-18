/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 * title: kth-largest-element-in-an-array
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "utils/debug_print.hpp"

using namespace std;

// @lc code=start
struct Compare {
  bool operator()(const int a, const int b) const { return a > b; }
};

class Solution {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, Compare> pq;
    for (int i : nums) {
      if (pq.size() < k) pq.push(i);
      else{
        if (i > pq.top()) pq.push(i);
        if (pq.size() > k) pq.pop();
      }
    }
    return pq.top();
  }
};
// @lc code=end

int main() {
  // vector<int> nums = {2, 1};
  vector<int> nums = {3, 2, 1, 5, 6, 4};
  int k = 2;
  Solution sol;
  auto v = sol.findKthLargest(nums, k);
  fmt::print("{}\n", v);
  return 0;
}
