/*
 * @lc app=leetcode.cn id=452 lang=cpp
 *
 * [452] 用最少数量的箭引爆气球
 * title: minimum-number-of-arrows-to-burst-balloons
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
  int findMinArrowShots(vector<vector<int>>& points) {
    sort(points.begin(), points.end(),
         [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; });
    int arrows = 1;
    int start = points[0][0], end = points[0][1];
    for (int i = 1; i < points.size(); i++) {
      int a = points[i][0];
      int b = points[i][1];
      if (a > end) {
        arrows++;
        start = a;
        end = b;
      } else {
        start = max(start, a);
        end = min(end, b);
      }
    }
    return arrows;
  }
};
// @lc code=end

int main() {
  // vector<vector<int>> points = {{10,16},{2,8},{1,6},{7,12}};
  vector<vector<int>> points = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
  Solution sol;
  auto v = sol.findMinArrowShots(points);
  fmt::print("{}\n", v);
  return 0;
}
