/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 * title: maximum-subarray
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    vector<int> dp(nums.size());
    dp[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
      dp[i] = max(dp[i - 1] + nums[i], nums[i]);
    }
    return *max_element(dp.begin(), dp.end());
  }
};

class Solution_Recur {
 public:
  struct Status {
    int lSum, rSum, mSum, iSum;
  };

  Status pushUp(Status l, Status r) {
    int iSum = l.iSum + r.iSum;
    int lSum = max(l.lSum, l.iSum + r.lSum);
    int rSum = max(r.rSum, r.iSum + l.rSum);
    int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
    return (Status){lSum, rSum, mSum, iSum};
  };

  Status get(vector<int>& a, int l, int r) {
    if (l == r) {
      return (Status){a[l], a[l], a[l], a[l]};
    }
    int m = (l + r) >> 1;
    Status lSub = get(a, l, m);
    Status rSub = get(a, m + 1, r);
    return pushUp(lSub, rSub);
  }

  int maxSubArray(vector<int>& nums) {
    return get(nums, 0, nums.size() - 1).mSum;
  }
};
// @lc code=end

int main() {
  Solution_Recur sol;
  vector<int> v{-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int sum = sol.maxSubArray(v);
  fmt::print("{}\n", sum);
  return 0;
}
