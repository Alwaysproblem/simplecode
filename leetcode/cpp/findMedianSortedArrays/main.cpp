/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 * title: median-of-two-sorted-arrays
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

// @lc code=start
class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
      return findMedianSortedArrays(nums2, nums1);
    }
    int m = nums1.size(), n = nums2.size();
    int left = 0, right = m;
    int median1 = 0, median2 = 0;
    while (left <= right) {
      // the mid of bi-search.
      int i = (left + right) / 2;
      // the middle of two arrays for index of the second array.
      // since the total numbers is constant, we can get j
      // (the index of second array) from i.
      // this means the (left set - the right set) == 1 if (m + n) % 2 != 0.
      int j = (m + n + 1) / 2 - i;

      // 1 3 | 5
      // 2 4 | 6 7

      int nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);  // 3
      int nums_i = (i == m ? INT_MAX : nums1[i]);        // 5
      int nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);  // 4
      int nums_j = (j == n ? INT_MAX : nums2[j]);        // 6

      if (nums_im1 <= nums_j) {
        median1 = max(nums_im1, nums_jm1);
        median2 = min(nums_i, nums_j);
        left = i + 1;
      } else {
        right = i - 1;
      }
    }
    return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
  }
};
// @lc code=end

int main() {
  vector<int> nums1 = {1, 3, 5};
  vector<int> nums2 = {2, 4, 6, 7};
  Solution sol;
  double v = sol.findMedianSortedArrays(nums1, nums2);
  fmt::print("{}\n", v);
  return 0;
}
