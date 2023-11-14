/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
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
  int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size() + 1, 1);
    for (int i = 0; i < nums.size(); i++) {
      for (int j = 0; j <= i; j++) {
        if (nums[j] < nums[i]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
    }
    return *max_element(dp.begin(), dp.end());
  }
  int lengthOfLIS_nlogn(vector<int>& nums) {
    vector<vector<int>> top(nums.size(), vector<int>());
    int piles = 0;
    for (int i = 0; i < nums.size(); i++) {
      int poker = nums[i];

      int left = 0, right = piles;
      while (right > 0 && left < right) {
        int mid = left + (right - left) / 2;
        if (top[mid].back() == poker) {
          right = mid;
        } else if (top[mid].back() > poker) {
          right = mid;
        } else if (top[mid].back() < poker) {
          left = mid + 1;
        }
      }

      if (left == piles) piles++;
      // top[left] = poker;
      top[left].push_back(poker);
    }
    // fmt::print("{}\n", top);
    return piles;
  }
};
// @lc code=end

int main() {
  Solution sol;
  vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
  int v = sol.lengthOfLIS_nlogn(nums);
  fmt::print("{}\n", v);
  return 0;
}
