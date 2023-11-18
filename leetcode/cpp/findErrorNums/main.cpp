/*
 * @lc app=leetcode.cn id=645 lang=cpp
 *
 * [645] 错误的集合
 * title: set-mismatch
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
  vector<int> findErrorNums(vector<int>& nums) {
    // 1 2 4 2
    // 0 1 2 3
    // in normal, the nums is respond to index
    // if the index is duplicate, the value is negative
    // if the index is missing, the value is positive
    // for example:
    // for `4`, it will change the sign of `nums[3]` to negative
    // when it comes to `2` again, it will find the duplicate element,
    // and will change the sign of `nums[1]` to negative, but `nums[1]` is
    // already negative. So we find the duplicate element is 1(idx) + 1.
    // Similarly, if there is missing element, we find it by checking the
    // positive element in nums.
    int n = nums.size();
    int dup = -1, idx = 0;
    for (int i = 0; i < n; i++) {
      idx = (int)abs(nums.at(i)) - 1;
      if (nums.at(idx) < 0) {
        dup = idx;
      } else {
        nums.at(idx) *= -1;
      }
    }
    int missing = -1;
    for (int i = 0; i < n; i++) {
      if (nums.at(i) > 0) {
        missing = i + 1;
      }
    }
    // fmt::print("{}, dup: {}, missing: {}\n", nums, dup, missing);
    return vector<int>{dup + 1, missing};
    // return vector<int>();
  }
};
// @lc code=end

int main() {
  vector<int> nums = {1, 2, 4, 2};
  // vector<int> nums = {1, 2, 4, 4, 7, 6}; this will cause malloc error it is
  // new things for debug! you can try it.
  Solution sol;
  vector<int> v = sol.findErrorNums(nums);
  fmt::print("{}\n", v);
  return 0;
}
