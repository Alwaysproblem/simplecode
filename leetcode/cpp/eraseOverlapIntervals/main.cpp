/*
 * @lc app=leetcode.cn id=435 lang=cpp
 *
 * [435] 无重叠区间
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// @lc code=start
class Solution {
 public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;

    sort(
        intervals.begin(), intervals.end(),
        [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });

    int end = intervals[0][1];
    int count = 0;

    for (int i = 1; i < intervals.size(); i++) {
      if (intervals[i][0] >= end) {
        end = intervals[i][1];
      } else {
        count++;
        end = min(end, intervals[i][1]);
      }
    }

    return count;
  }
};
// @lc code=end

int main() {
  vector<vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
  Solution sol;
  auto v = sol.eraseOverlapIntervals(intervals);
  fmt::print("{}\n", v);
  return 0;
}
