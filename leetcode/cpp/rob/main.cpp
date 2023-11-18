/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 * title: house-robber
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
  int rob(vector<int>& nums) {
    vector<int> dp(nums.size() + 1);
    dp[0] = 0;
    for (int i = 1; i <= nums.size(); i++) {
      if (i - 2 > 0)
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
      else
        dp[i] = max(dp[i - 1], dp[0] + nums[i - 1]);
    }
    // fmt::print("{}\n", dp);
    return dp.back();
  }
};
// @lc code=end

int main() {
  vector<int> nums = {2, 7, 9, 3, 1};
  Solution sol;
  int v = sol.rob(nums);
  fmt::print("{}\n", v);
  return 0;
}
