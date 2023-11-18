/*
 * @lc app=leetcode.cn id=45 lang=cpp
 *
 * [45] 跳跃游戏 II
 * title: jump-game-ii
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
  int jump(vector<int>& nums) {
    int n = nums.size();
    int cnt = 0;
    int i = 0;
    int idx = 0;
    while (i < n - 1) {
      if (nums[i] < 1) return -1;
      if (i + nums[i] >= n - 1) return cnt + 1;
      int maxPos = nums[i + 1];
      idx = i + 1;
      for (int j = 1; j <= nums[i]; j++) {
        if (maxPos <= nums[i + j] + j) {
          idx = i + j;
          // takeways: I need to find the maximum step
          // I can make from the current position
          maxPos = nums[i + j] + j;
        }
      }
      cnt++;
      i = idx;
    }
    return cnt;
  }
};
// @lc code=end

int main() {
  vector<int> nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 0};
  Solution sol;
  auto v = sol.jump(nums);
  fmt::print("{}\n", v);
  return 0;
}
