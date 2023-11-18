/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 * title: find-first-and-last-position-of-element-in-sorted-array
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
  int searchLowerbound(vector<int>& nums, int target) {
    if (!nums.size()) return -1;
    int left = 0, right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
      mid = left + (right - left) / 2;
      if (nums[mid] == target) {
        right = mid - 1;
      } else if (nums[mid] > target) {
        right = mid - 1;
      } else if (nums[mid] < target) {
        left = mid + 1;
      }
    }
    if (left >= nums.size()) return -1;
    return target == nums[left] ? left : -1;
  }
  int searchUpperbound(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
      mid = left + (right - left) / 2;
      if (nums[mid] == target) {
        left = mid + 1;
      } else if (nums[mid] > target) {
        right = mid - 1;
      } else if (nums[mid] < target) {
        left = mid + 1;
      }
    }
    if (right < 0) return -1;
    return target == nums[right] ? right : -1;
  }
  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res;
    int lower = searchLowerbound(nums, target);
    int upper = searchUpperbound(nums, target);
    res.push_back(lower);
    res.push_back(upper);
    return res;
  }
};
// @lc code=end

int main() {
  Solution s;
  vector<int> v{5, 7, 7, 8, 8, 10};
  vector<int> r = s.searchRange(v, 8);
  fmt::print("The index should be {}\n", r);
  return 0;
}
