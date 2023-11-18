# LeetCode 学习笔记

-------------

## 会议室 II

给你一个会议时间安排的数组 intervals ，每个会议时间都会包括开始和结束的时间 intervals[i] = [starti, endi] ，返回 所需会议室的最小数量 。

示例 1：

```
输入：intervals = [[0,30],[5,10],[15,20]]
输出：2
```

示例 2：

```
输入：intervals = [[7,10],[2,4]]
输出：1
```

提示：

* `1 <= intervals.length <= 10^4`
* `0 <= starti < endi <= 10^6`

```cpp
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
```
