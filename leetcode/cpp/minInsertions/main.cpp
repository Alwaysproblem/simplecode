/*
 * @lc app=leetcode.cn id=1312 lang=cpp
 *
 * [1312] 让字符串成为回文串的最少插入次数
 * title: minimum-insertion-steps-to-make-a-string-palindrome
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
  int minInsertions(string s) {
    if (!s.size()) return 0;
    vector<vector<int>> dp(s.size(), vector<int>(s.size()));
    for (int i = 0; i < s.size(); i++) {
      dp[i][i] = 0;
    }

    for (int start = s.size() - 1; start >= 0; start--) {
      for (int end = start + 1; end < s.size(); end++) {
        if (s[start] == s[end])
          dp[start][end] = dp[start + 1][end - 1];
        else
          dp[start][end] = min(dp[start + 1][end], dp[start][end - 1]) + 1;
      }
    }
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.front().back();
  }
};
// @lc code=end

int main() {
  string s = "leetcode";
  Solution sol;
  int v = sol.minInsertions(s);
  fmt::print("{}\n", v);
  return 0;
}
