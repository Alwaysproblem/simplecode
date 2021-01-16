#
# @lc app=leetcode.cn id=4 lang=python3
#
# [4] 寻找两个正序数组的中位数
#
from typing import List

# @lc code=start
from math import inf
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        def function(nums1, nums2):
            if len(nums1) > len(nums2):
                return function(nums2, nums1)
            
            m = len(nums1)
            n = len(nums2)
            l, r = 0, m
            med1 , med2 = 0, 0

            while l <= r:
                i = (l + r) // 2
                j = (m + n + 1) // 2 - i

                num_im1 = -inf if i == 0 else nums1[i - 1]
                num_i = inf if i == m else nums1[i]
                num_jm1 = -inf if j == 0 else nums2[j - 1]
                num_j = inf if j == n else nums2[j]

                if num_im1 <= num_j:
                    med1, med2 = max(num_im1, num_jm1), min(num_i, num_j)
                    l = i + 1
                else:
                    r = i - 1
            return (med1 + med2) / 2 if (m + n) % 2 == 0 else med1
        
        return function(nums1, nums2)
# @lc code=start