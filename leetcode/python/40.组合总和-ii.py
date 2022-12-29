#
# @lc app=leetcode.cn id=40 lang=python3
#
# [40] 组合总和 II

from  typing import *
# @lc code=start
class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        coms = list()
        com = list()

        if not candidates:
            return []
        
        def backtrack(com, cans, target):
            if sum(com) == target:
                coms.append(com.copy())
                return
            
            if target < sum(com):
                return

            cs =  cans.copy()
            for ind, i in enumerate(cans):
                com.append(i)
                cs.pop(0)
                backtrack(com, cs, target)
                cs.append(i)
                com.pop()
        
        backtrack(com, sorted(candidates), target)

        return coms


# @lc code=end

if __name__ == '__main__':
    print(Solution().combinationSum2(candidates = [10,1,2,7,6,1,5], target = 8,))