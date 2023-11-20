/*
 * @lc app=leetcode.cn id=122 lang=cpp
 *
 * [122]  买卖股票的最佳时机 II
 * title: best-time-to-buy-and-sell-stock-ii
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
* This problem k is Infinity, so k - 1 = k = infinity.
* dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
* dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
*/
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int N = prices.size();
    vector<vector<int>> dp(N + 1, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i <= N; i++) {
      dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i - 1]);
      dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i - 1]);
    }
    // print2D(dp);
    return dp[N][0];
  }
};
// @lc code=end

int main() {
  vector<int> prices = {1,2,3,4,5};
  // vector<int> prices = {7, 1, 5, 3, 6, 4};
  // vector<int> prices = {1};
  Solution sol;
  auto v = sol.maxProfit(prices);
  fmt::print("{}\n", v);
  return 0;
}
