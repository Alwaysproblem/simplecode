/*
 * @lc app=leetcode.cn id=253 lang=cpp
 *
 * [253] 会议室 II
 * title: meeting-rooms-ii
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "utils/debug_print.hpp"

using namespace std;

// @lc code=start
// The idea is the same as the `car-pooling`
// 0 ---- 5 ---- 10 ---- 15 ---- 20 ---- 30
// +1     +1     -1      +1      -1      -1
// and then we take the max sum during the loop.
// NB: 
// 0 ---- 13 - 13 ----- 15
// +1     -1   +1       -1
// if we consider the boundary case, the -1 is in front of +1.
class Solution {
 public:
  int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<vector<int>> schedule_table;
    int room = 0;
    int max_room = 0;
    for (auto inter : intervals) {
      schedule_table.push_back({inter[0], 1});
      schedule_table.push_back({inter[1], -1});
    }
    sort(schedule_table.begin(), schedule_table.end(),
         [](const vector<int> &a, const vector<int> &b) {
           if (a[0] < b[0]) {
             return true;
           } else if (a[0] == b[0]) {
             return a[1] < b[1];
           };
           return false;
         });

    for (const auto& st : schedule_table) {
      room += st[1];
      max_room = max(room, max_room);
    }
    return max_room;
  }
};
// @lc code=end

int main() {
  vector<vector<int>> intervals{{0, 30}, {5, 10}, {15, 20}};
  // vector<vector<int>> intervals{{7, 10}, {2, 4}};
  // vector<vector<int>> intervals{{13, 15}, {1, 13}};
  Solution sol;
  auto v = sol.minMeetingRooms(intervals);
  fmt::print("{}\n", v);
  return 0;
}
