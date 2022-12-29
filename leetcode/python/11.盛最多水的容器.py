#
# @lc app=leetcode.cn id=11 lang=python3
#
# [11] 盛最多水的容器
#
from  typing import * 
# @lc code=start
class Solution:
    def maxArea(self, height: List[int]) -> int:
        left = 0
        right = len(height) - 1

        area_max = 0

        while left <= right:
            area_max = max(area_max, 
                            min(height[left], 
                                    height[right]) * (right - left))
            if height[left] > height[right]:
                right -= 1
            else:
                left += 1

        return area_max
# @lc code=end
if __name__ == "__main__":
    print(Solution().maxArea([10, 9, 8, 7, 6, 5, 4, 3, 2, 1]))