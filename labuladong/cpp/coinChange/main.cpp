#include <iostream>
#include <unordered_map>
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>

using namespace std;

class Solution {
public:
    int INF = 1e9;
    int dp_min = INF;
    int coinChange(vector<int>& coins, int amount) {
      vector<int> dp(amount + 1, INF);
      dp.at(0) = 0;
      for (int a = 1; a < amount + 1; ++a){
        for (int c : coins){
          if 	(a >= c){
            dp.at(a) = min(dp.at(a), dp.at(a - c) + 1);
          }
        }
      }
      return dp.at(amount) == INF? -1 : dp.at(amount);
    }
}; 

int main()
{
  Solution s;
  vector<int> v{1, 2, 5};
  int result = s.coinChange(v, 11);
  fmt::print("{} coins.\n", result);
  return 0;
}
