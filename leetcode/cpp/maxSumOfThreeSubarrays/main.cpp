/*
 * @lc app=leetcode.cn id=689 lang=cpp
 *
 * [689] 三个无重叠子数组的最大和
 * title: maximum-sum-of-3-non-overlapping-subarrays
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
/*
 * we take the window size is 3 * k and slide through the all nums.
 * since there is no overlaps among those subarray.
 *
 *
 * 1     2     1     2     6     7     5     1
 * [  1  ]
 *      [  2  ]
 *            [  3  ]
 *
 * 1     2     1     2     6     7     5     1
 *       [  1  ]
 *            [  2  ]
 *                  [  3  ]
 *
 * 1     2     1     2     6     7     5     1
 *             [  1  ]
 *                   [  2  ]
 *                         [  3  ]
 *
 * ----------------------------------------------
 *
 * 1     2     1     2     6     7     5     1
 *             [  1  ]
 *                   [  2  ]
 *                         [  3  ]
 *             a     b     c     i
 *
 * a = i - 3k + 1
 * b = i - 2k + 1
 * c = i -  k + 1
 *
 * so, the sum will be:
 *
 * sum1 += num[b];
 * sum2 += num[c];
 * sum3 += num[i];
 *
 * max_sum1 is the max sum of subarray 1.
 * max_sum2 is the max sum of subarray 1 and 2.
 * max_sum3 is the max sum of subarray 1 and 2 and 3.
 *
 */
class Solution {
 public:
  vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    vector<int> ans{};
    int sum_1 = 0, sum_2 = 0, sum_3 = 0;
    int max_sum_1 = 0, max_sum_2 = 0, max_sum_3 = 0;
    int max_sum_1_sidx = 0, max_sum_2_sidx = 0, max_sum_12_sidx = 0, max_sum_3_sidx = 0;
    for (int i = 2 * k; i < nums.size(); i++) {
      sum_1 += nums[i - 2 * k];
      sum_2 += nums[i - k];
      sum_3 += nums[i];
      if (i >= 3 * k - 1) {
        if (sum_1 > max_sum_1) {
          max_sum_1 = sum_1;
          max_sum_1_sidx = i - 2 * k - (k - 1);
        }
        if (max_sum_1 + sum_2 > max_sum_2) {
          max_sum_2 = max_sum_1 + sum_2;
          // NB: need to save the first window idx.
          max_sum_12_sidx = max_sum_1_sidx;
          max_sum_2_sidx = i - k - (k - 1);
        }
        if (max_sum_2 + sum_3 > max_sum_3) {
          max_sum_3 = max_sum_2 + sum_3;
          max_sum_3_sidx = i - (k - 1);
          // use the saved first window idx to get correct ans.
          ans= {max_sum_12_sidx, max_sum_2_sidx, max_sum_3_sidx};
        }
        sum_1 -= nums[i - 2 * k - (k - 1)];
        sum_2 -= nums[i - k - (k - 1)];
        sum_3 -= nums[i - (k - 1)];
      }
    }
    return ans;
  }
};
// @lc code=end

int main() {
  // vector<int> nums = {1,2,1,2,6,7,5,1};
  // int k = 2;
  vector<int> nums = {4, 5, 10, 6, 11, 17, 4, 11, 1, 3};
  int k = 1;
  Solution sol;
  auto v = sol.maxSumOfThreeSubarrays(nums, k);
  fmt::print("{}\n", v);
  return 0;
}
