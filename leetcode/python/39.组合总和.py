#
# @lc app=leetcode.cn id=39 lang=python3
#
# [39] 组合总和
#
from typing import *
# @lc code=start
class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        if len(candidates) == 0:
            return []
        
        n = len(candidates) - 1
        com = []
        coms = []

        def backtrace(com):

            if sum(com) == target:
                coms.append(com.copy())
                return
            if sum(com) < target:
                for i in candidates:
                    if len(com) == 0 or i >= com[-1]:
                        com.append(i)
                        backtrace(com)
                        com.pop()

        backtrace(com)

        return coms
# @lc code=end

