/*
 * @lc app=leetcode.cn id=1094 lang=cpp
 *
 * [1094] 拼车
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
  bool carPooling(vector<vector<int>>& trips, int capacity) {
    int nums_pass = 0, from_ = 0, to_ = 0;
    vector<int> diff(1001);
    for (vector<int>& tr : trips) {
      nums_pass = tr[0];
      from_ = tr[1];
      to_ = tr[2];
      diff[from_] += nums_pass;
      diff[to_] += -nums_pass;
    }
    // fmt::print("{}\n", diff);
    int total_sum = 0;
    for (int& x : diff) {
      total_sum += x;
      if (total_sum > capacity) return false;
    }
    return true;
  }
};
// @lc code=end

int main() {
  vector<vector<int>> trips = {{2, 1, 5}, {3, 5, 7}};
  int capacity = 3;
  Solution sol;
  bool v = sol.carPooling(trips, capacity);
  fmt::print("{}\n", v);
  return 0;
}
