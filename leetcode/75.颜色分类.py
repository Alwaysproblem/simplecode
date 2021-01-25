#
# @lc app=leetcode.cn id=75 lang=python3
#
# [75] 颜色分类
#
from typing import List
# note Counting sort
# @lc code=start
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        def CountSort(nums):
            # if min(nums) > 0:
            #     cnt_list = [0] * max(nums)
            # else:
            cnt_list = [0] * (abs(max(nums)) + abs(min(nums)) + 1)
            delta = min(nums)
            res = []

            for i in nums:
                cnt_list[i - delta] += 1
            
            for idx, cnt in enumerate(cnt_list):
                if cnt != 0:
                    res += [idx + delta] * cnt
            
            return res
        res = CountSort(nums)
        for idx, value in enumerate(res):
            nums[idx] = value

# @lc code=end

