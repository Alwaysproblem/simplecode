/*
 * @lc app=leetcode.cn id=494 lang=cpp
 *
 * [494] 目标和
 * title: target-sum
 */
#include "utils/debug_print.hpp"
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  /*
  assume that
  set A include all positive.
  set B include all negative.
  sum(A) - sum(B) == target
  sum(A) - sum(B) - sum(B) == target - sum(B)
  - 2 * sum(B) = target - sum(B) -sum(A)
  2 * sum(B) = sum(nums) - target
  */
  int pack(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(target + 1));

    for (int k = 0; k <= n; k++) dp[k][0] = 1;

    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= target; j++) {
        if (j >= nums[i - 1])
          dp[i][j] = dp[i - 1][j - nums[i - 1]] + dp[i - 1][j];
        else
          dp[i][j] = dp[i - 1][j];
      }
    }
    // print2D(dp);
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.back().back();
  }

  int findTargetSumWays(vector<int>& nums, int target) {
    int total_sum = 0;
    for (int x : nums) {
      total_sum += x;
    }
    if (total_sum < target || (total_sum - target) % 2) return 0;
    return pack(nums, (total_sum - target) / 2);
  }
};
// @lc code=end

int main() {
  vector<int> nums = {100, 100};
  int target = -400;
  Solution sol;
  int v = sol.findTargetSumWays(nums, target);
  fmt::print("{}\n", v);
  return 0;
}
