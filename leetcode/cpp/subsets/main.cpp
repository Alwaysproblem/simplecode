/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 */
#include <fmt/ranges.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  vector<vector<int>> res{};
  unordered_map<int, int> visited{};
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> sol{};
    backtrack(nums, 0, sol);
    return res;
  }

  void backtrack(vector<int>& nums, int candidate_idx, vector<int>& solution) {
    if (candidate_idx > nums.size()) return;
    res.push_back(vector<int>(solution));
    for (int i = candidate_idx; i < nums.size(); i++) {
      solution.push_back(nums[i]);
      backtrack(nums, i + 1, solution);
      solution.pop_back();
    }
  }
};
// @lc code=end

int main() {
  Solution s;
  vector<int> v{1, 2, 3};
  vector<vector<int>> result = s.subsets(v);
  fmt::print("res: {}\n", result);
  return 0;
}
