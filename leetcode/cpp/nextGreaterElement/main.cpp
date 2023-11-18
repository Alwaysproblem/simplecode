/*
 * @lc app=leetcode.cn id=503 lang=cpp
 *
 * [503] 下一个更大元素 II
 * title: next-greater-element-ii
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  vector<int> nextGreaterElements(vector<int>& nums) {
    vector<int> ans(nums.size());
    stack<int> s{};
    for (int i = nums.size() * 2 - 1; i >= 0; i--) {
      while (!s.empty() && s.top() <= nums[i % nums.size()]) s.pop();
      ans[i % nums.size()] = s.empty() ? -1 : s.top();
      s.push(nums[i % nums.size()]);
    }
    return ans;
  }
};
// @lc code=end

int main() {
  vector<int> nums = {1, 2, 3, 4, 3};
  Solution sol;
  vector<int> v = sol.nextGreaterElements(nums);
  fmt::print("{}\n", v);
  return 0;
}
