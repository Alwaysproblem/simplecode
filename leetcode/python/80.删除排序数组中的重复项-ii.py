#
# @lc app=leetcode.cn id=80 lang=python3
#
# [80] 删除排序数组中的重复项 II
#
from typing import List
# @lc code=start
class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        i = 0
        K = 2

        for n in nums:
            if i < K or n != nums[i-K]:
                nums[i] = n
                i += 1
        return i

# @lc code=end

if __name__ == "__main__":
    s= Solution()
    a = [1,1, 1,]
    print(s.removeDuplicates(a))
    print(a)