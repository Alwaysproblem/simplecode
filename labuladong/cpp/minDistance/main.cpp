#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int minDistance(string word1, string word2) {
    vector<vector<int>> dp(word2.size() + 1, vector<int>(word1.size() + 1));
    for (int i = 1; i <= word1.size(); i++) {
      dp[0][i] = i;
    }
    for (int i = 1; i <= word2.size(); i++) {
      dp[i][0] = i;
    }
    for (int row = 1; row <= word2.size(); row++) {
      for (int col = 1; col <= word1.size(); col++) {
        if (word2[row - 1] == word1[col - 1]) {
          dp[row][col] = dp[row - 1][col - 1];  // skip
        } else {
          dp[row][col] = min(min(dp[row - 1][col],       // insertion
                                 dp[row - 1][col - 1]),  // replacement
                             dp[row][col - 1]            // deletion
                             ) +
                         1;
        }
      }
    }
    fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.back().back();
  }
};

int main() {
  string word1 = "", word2 = "a";
  Solution sol;
  int v = sol.minDistance(word1, word2);
  fmt::print("{}\n", v);
  return 0;
}
