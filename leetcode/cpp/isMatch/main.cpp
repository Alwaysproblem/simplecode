/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
 * title: regular-expression-matching
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
  bool match(const string &s, const string &p, int i, int j) {
    if (i == 0) {
      return false;
    }
    if (p[j - 1] == '.') {
      return true;
    }
    return s[i - 1] == p[j - 1];
  }

  /*
  f[i][j]=
    if (p[j] != ‘*’)
      f[i−1][j−1]    matches(s[i],p[j])
      false          otherwise
    else
      f[i−1][j] (match many times) or f[i][j−2] (match 0 times)   matches(s[i],p[j−1])
      f[i][j−2]                                                   otherwise
  */

  bool isMatch(string s, string p) {
    vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
    dp[0][0] = true;
    for (int i = 0; i <= s.size(); i++) {
      for (int j = 1; j <= p.size(); j++) {
        if (p[j - 1] != '*')
          if (match(s, p, i, j))
            dp[i][j] = dp[i - 1][j - 1];
          else
            dp[i][j] = false;
        else if (match(s, p, i, j - 1))
          dp[i][j] = dp[i][j - 2] || dp[i - 1][j];
        else
          dp[i][j] = dp[i][j - 2];
      }
    }
    print2D(dp);
    return dp.back().back();
  }
};
// @lc code=end

int main() {
  string s = "aa", p = "a*";
  Solution sol;
  bool v = sol.isMatch(s, p);
  fmt::print("{}\n", v);
  return 0;
}
