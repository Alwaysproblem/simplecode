/*
 * @lc app=leetcode.cn id=167 lang=cpp
 *
 * [167] 两数之和 II - 输入有序数组
 * title: two-sum-ii-input-array-is-sorted
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
// sorted List for nums
// 双指针算法
class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    // 左右指针
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
      int sum = nums[lo] + nums[hi];
      // 根据 sum 和 target 的比较，移动左右指针
      if (sum < target) {
        lo++;
      } else if (sum > target) {
        hi--;
      } else if (sum == target) {
        return {lo + 1, hi + 1};
      }
    }
    return {};
  }
};
// @lc code=end

int main() {
  Solution s;
  vector<int> v{1, 6, 3, 2, 5};
  vector<int> result = s.twoSum(v, 11);
  fmt::print("{}\n", result);
  return 0;
}
