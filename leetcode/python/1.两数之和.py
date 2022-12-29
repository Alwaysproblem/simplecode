#
# @lc app=leetcode.cn id=1 lang=python3
#
# [1] 两数之和
#
from typing import List
# @lc code=start
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:

        ind_table = dict()

        for ind, v in enumerate(nums):
            if target - v in ind_table:
                return [ind_table[target - v], ind]
            ind_table[v] = ind
        return []
# @lc code=end

if __name__ == "__main__":
    s = Solution()
    print(s.twoSum([3,2,4], 6))