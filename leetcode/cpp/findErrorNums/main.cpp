/*
 * @lc app=leetcode.cn id=645 lang=cpp
 *
 * [645] 错误的集合
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  vector<int> findErrorNums(vector<int>& nums) {
    int n = nums.size();
    int dup = -1, idx = 0;
    for (int i = 0; i < n; i++) {
      idx = (int)abs(nums.at(i)) - 1;
      if (nums.at(idx) < 0) {
        dup = idx;
      } else {
        nums.at(idx) *= -1;
      }
    }
    int missing = -1;
    for (int i = 0; i < n; i++) {
      if (nums.at(i) > 0) {
        missing = i + 1;
      }
    }
    // fmt::print("{}, dup: {}, missing: {}\n", nums, dup, missing);
    return vector<int>{dup + 1, missing};
    // return vector<int>();
  }
};
// @lc code=end

int main() {
  vector<int> nums = {1, 2, 4, 4, 6, 6};
  // vector<int> nums = {1, 2, 4, 4, 7, 6}; this will cause malloc error it is
  // new things for debug! you can try it.
  Solution sol;
  vector<int> v = sol.findErrorNums(nums);
  fmt::print("{}\n", v);
  return 0;
}
