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
    vector<int> s{};
    for (int i : nums) visited[i] = 0;
    int empty_set = *min_element(nums.begin(), nums.end()) - 1;
    backtrack(nums, s, visited, empty_set);
    return res;
  }

  void backtrack(vector<int>& nums, vector<int>& solution,
                 unordered_map<int, int> visited, int empty_set) {
    if (!solution.empty() && solution.back() == empty_set) {
      solution.pop_back();
      if (solution.size() <= visited.size()) res.push_back(solution);
      solution.push_back(empty_set);
      return;
    }

    for (int ix = -1; ix < int(nums.size()); ++ix) {
      if (ix < 0) {
        solution.push_back(empty_set);
        backtrack(nums, solution, visited, empty_set);
        solution.pop_back();
      } else {
        if (visited[nums[ix]] != 0) continue;
        solution.push_back(nums[ix]);
        visited[nums[ix]] = 1;
        backtrack(nums, solution, visited, empty_set);
        visited[nums[ix]] = 0;
        solution.pop_back();
        visited[nums[ix]] = 1;
      }
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
