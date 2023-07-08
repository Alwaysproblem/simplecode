#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    int total_sum = 0;
    for (int x : nums) {
      total_sum += x;
    }
    if (total_sum % 2) return false;
    int half_total_sum = total_sum / 2;
    vector<vector<bool>> dp(nums.size() + 1, vector<bool>(half_total_sum + 1));
    dp[0][0] = true;
    for (int i = 1; i <= nums.size(); i++) {
      dp[i][0] = true;
    }

    for (int i = 1; i <= nums.size(); i++) {
      for (int j = 1; j <= half_total_sum; j++) {
        if (j - nums[i - 1] >= 0)
          dp[i][j] = dp[i - 1][j - nums[i - 1]] || dp[i - 1][j];
        else
          dp[i][j] = dp[i - 1][j];
      }
    }
    fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return dp.back().back();
  }
};

int main() {
  vector<int> nums{1, 2, 3, 4};
  Solution sol;
  bool v = sol.canPartition(nums);
  fmt::print("{}\n", v);
  return 0;
}
