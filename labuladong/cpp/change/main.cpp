#include <iostream>
#include <unordered_map>
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>

using namespace std;

class Solution {
public:
    int change(int amount, vector<int>& coins) {
      vector<vector<int>> dp(amount+1, vector<int>(coins.size() + 1));
      for (int j = 1; j <= coins.size(); ++j) {
          dp.at(0).at(j) = 1;
      }
      for (int a = 0; a <= amount; ++a) {
          dp.at(a).at(0) = 0;
      }
      for (int a = 1; a <= amount; ++a) {
        for (int j = 1; j <= coins.size(); ++j) {
          if (a > coins.at(j - 1))
            dp.at(a).at(j) = dp.at(a).at(j - 1) + dp.at(a - coins.at(j - 1)).at(j);
          else if (a == coins.at(j - 1)) 
            dp.at(a).at(j) = dp.at(a).at(j - 1) + 1;
          else
            dp.at(a).at(j) = dp.at(a).at(j - 1);
        }
      }
      fmt::print("{}", dp);
      return dp.at(amount).at(coins.size());
    }
};

int main()
{
  Solution s;
  vector<int> v{1, 2, 5};
  int res = s.change(5, v);
  fmt::print("\n{}\n", res);
  return 0;
}
