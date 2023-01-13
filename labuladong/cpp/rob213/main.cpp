#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int robRange(vector<int>& nums, int start, int end) {
    vector<int> dp(nums.size() + 1);
    dp[0] = 0;
    for (int i = start + 1; i <= end; i++) {
      if (i - 2 > 0)
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
      else
        dp[i] = max(dp[i - 1], dp[0] + nums[i - 1]);
    }
    fmt::print("{}\n", dp);
    return dp[end];
  }

  int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    int s1 = robRange(nums, 1, n - 1);
    int s2 = robRange(nums, 1, n - 2) + nums[n - 1];
    int s3 = robRange(nums, 2, n - 1) + nums[0];
    fmt::print("{}, {}, {}\n", s1, s2, s3);
    return max(max(s1, s2), s3);
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 1};
  // vector<int> nums = {2, 7, 9, 3, 1};
  Solution sol;
  int v = sol.rob(nums);
  fmt::print("{}\n", v);
  return 0;
}
