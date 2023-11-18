/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 * title: coin-change
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <limits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  int INF = std::numeric_limits<int>::max();
  int dp_min = INF;
  int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INF);
    dp.at(0) = 0;
    for (int a = 1; a < amount + 1; ++a) {
      for (int c : coins) {
        if (a >= c) {
          dp.at(a) = min(dp.at(a), dp.at(a - c) + 1);
        }
      }
    }
    return dp.at(amount) == INF ? -1 : dp.at(amount);
  }
};
// @lc code=end

int main() {
  Solution s;
  vector<int> v{1, 2, 5};
  int result = s.coinChange(v, 11);
  fmt::print("{} coins.\n", result);
  return 0;
}
