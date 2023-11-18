/*
 * @lc app=leetcode.cn id=887 lang=cpp
 *
 * [887] 鸡蛋掉落
 * title: super-egg-drop
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
  int superEggDrop(int K, int N) {
    // define a problem that you have k eggs,
    // and drop m times, at most the level you can achieve.
    vector<vector<double>> dp(K + 1, vector<double>(N + 1));
    for (int m = 1; m <= N && dp[K][m] < N; m++) {
      for (int k = 1; k <= K; k++) {
        dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1;
      }
    }
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    for (int i = 0; i <= N; i++) {
      if (dp[K][i] >= N) {
        return i;
      }
    }
    return 0;
  }
};
// @lc code=end

int main() {
  int k = 10, n = 100;
  Solution sol;
  int v = sol.superEggDrop(k, n);
  fmt::print("{}\n", v);
  return 0;
}
