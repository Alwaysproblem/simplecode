#
# @lc app=leetcode.cn id=90 lang=python3
#
# [90] 子集 II
#
from typing import List
# @lc code=start
class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:

        def Subset(nums: list):
            if len(nums) == 0:
                return [set()]
            if len(nums) == 1:
                return [set(), set([nums[0]])]
            
            k = nums.pop()
            res, new_res = Subset(nums)

            res_ = []
            for i in res:
                co = i.copy()
                co.add(k)
                res_.append(co)
            
            new_res = len(res_)

            res_ += res

            return res_
        return Subset(nums)
# @lc code=end

if __name__ == "__main__":
    s = Solution()
    print(s.subsetsWithDup([1,2,2]))
