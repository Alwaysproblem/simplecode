/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
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
  int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int area_max = 0;
    while (left < right) {
      area_max =
          max(area_max, min(height[left], height[right]) * (right - left));
      if (height[left] > height[right])
        right--;
      else
        left++;
    }
    return area_max;
  }
};
// @lc code=end

int main() {
  vector<int> height = {1, 8, 100, 2, 100, 4, 8, 3, 7};
  Solution sol;
  auto v = sol.maxArea(height);
  fmt::print("{}\n", v);
  return 0;
}
