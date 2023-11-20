/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123]  买卖股票的最佳时机 III
 * title: best-time-to-buy-and-sell-stock-iii
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "utils/debug_print.hpp"

using namespace std;

// @lc code=start
/*
* dp[n][k][1] 的含义就是：
* 今天是第n天，至今最多进行 k 次交易 并且我现在手上持有着股票。
* 再比如 dp[n][k][0]:
* 今天是第n天，至今最多进行 k 次交易 并且我现在手上没有股票。
* 
* ```
* base case：
* dp[-1][...][0] = dp[...][0][0] = 0
* dp[-1][...][1] = dp[...][0][1] = -infinity
* 
* 状态转移方程：
* dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
* dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
* ```
* 
*/
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int N = prices.size();
    int K = 2;
    vector<vector<vector<int>>> dp(N + 1,
                                   vector<vector<int>>(K + 1, vector<int>(2)));

    for (int k = 0; k <= K; k++) {
      dp[0][k][0] = 0;
      dp[0][k][1] = -prices[0];
    }

    for (int i = 1; i <= N; i++) {
      for (int k = 1; k <= K; k++) {
        dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i - 1]);
        dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i - 1]);
      }
    }
    return dp[N][K][0];
  }
};
// @lc code=end

int main() {
  // vector<int> prices = {1, 2, 3, 4, 5};
  vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
  // vector<int> prices = {7, 1, 5, 3, 6, 4};
  Solution sol;
  auto v = sol.maxProfit(prices);
  fmt::print("{}\n", v);
  return 0;
}
