#
# @lc app=leetcode.cn id=152 lang=python3
#
# [152] 乘积最大子数组
#
from typing import *
# @lc code=start
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        if len(nums) == 1:
            return nums[0]

        max_dp = [0] * (len(nums) + 1)
        max_dp[0] = nums[0]
        min_dp = [0] * (len(nums) + 1)
        min_dp[0] = nums[0]

        for ind in range(1, len(nums)):
            max_dp[ind] = max(max_dp[ind - 1] * nums[ind], min_dp[ind - 1] * nums[ind], nums[ind])
            min_dp[ind] = min(max_dp[ind - 1] * nums[ind], min_dp[ind - 1] * nums[ind], nums[ind])

        ans = max(max_dp)
        return ans

# @lc code=end

if __name__ == "__main__":
    print(Solution().maxProduct([2,3,-2,4]))