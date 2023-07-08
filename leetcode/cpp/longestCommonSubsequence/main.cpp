#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

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
    fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.back().back();
  }
};

int main() {
  Solution sol;
  string text1 = "abc", text2 = "def";
  int v = sol.longestCommonSubsequence(text1, text2);
  fmt::print("{}\n", v);
  return 0;
}
