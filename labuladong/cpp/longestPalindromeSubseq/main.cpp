#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestPalindromeSubseq(string s) {
    if (!s.size()) return 0;
    vector<vector<int>> dp(s.size(), vector<int>(s.size()));
    for (int i = 0; i < s.size(); i++) {
      dp[i][i] = 1;
    }

    for (int start = s.size() - 1; start >= 0; start--) {
      for (int end = start + 1; end < s.size(); end++) {
        if (s[start] == s[end])
          dp[start][end] = dp[start + 1][end - 1] + 2;
        else
          dp[start][end] = max(dp[start + 1][end], dp[start][end - 1]);
      }
    }
    fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.front().back();
  }
};

int main() {
  string s = "bbbab";
  Solution sol;
  int v = sol.longestPalindromeSubseq(s);
  fmt::print("{}\n", v);
  return 0;
}
