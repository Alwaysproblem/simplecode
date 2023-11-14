/*
 * @lc app=leetcode.cn id=312 lang=cpp
 *
 * [312] 你可以获得的最大硬币数目
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
  int maxCoins(vector<int>& nums) {
    int n = nums.size();
    vector<int> scores(nums.size() + 2, 1);
    for (int i = 1; i <= nums.size(); i++) {
      scores[i] = nums[i - 1];
    }

    vector<vector<int>> dp(scores.size(), vector<int>(scores.size(), 0));
    for (int i = n; i >= 0; i--) {
      for (int j = i + 1; j < n + 2; j++) {
        for (int k = i + 1; k < j; k++) {
          // i OOO k OOO j
          // i {dp[i][k]} k {dp[k][j]} j
          // if we got dp[i][k] and dp[k][j]
          // then all balloons between i and k have been burst
          // as well as those between k and j.
          // so the maximum coins we can get is the sum of dp[i][k], dp[k][j]
          // and scores[i] * scores[k] * scores[j]
          dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] +
                                       scores[i] * scores[k] * scores[j]);
        }
      }
    }
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.front().back();
  }
};
// @lc code=end

int main() {
  vector<int> nums = {3, 1, 5, 8};
  Solution sol;
  int v = sol.maxCoins(nums);
  fmt::print("{}\n", v);
  return 0;
}
