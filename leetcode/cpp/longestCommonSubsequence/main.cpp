/*
 * @lc app=leetcode.cn id=1143 lang=cpp
 *
 * [1143] 最长公共子序列
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "utils/print_2d.hpp"

using namespace std;

// @lc code=start
class Solution {
 public:
  int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
    for (int i = 1; i <= text1.size(); i++) {
      for (int j = 1; j <= text2.size(); j++) {
        if (text1[i - 1] == text2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    // print2D(dp);
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.back().back();
  }
};
// @lc code=end

int main() {
  Solution sol;
  string text1 = "abc", text2 = "def";
  int v = sol.longestCommonSubsequence(text1, text2);
  fmt::print("{}\n", v);
  return 0;
}
