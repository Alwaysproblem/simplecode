#
# @lc app=leetcode.cn id=347 lang=python3
#
# [347] 前 K 个高频元素
#
from typing import *
# @lc code=start
from collections import Counter
from heapq import heappushpop, heappush, heappop
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        cnt = dict(Counter(nums))
        index = [value for _, value in cnt.items() ]

        pq = []

        for ind in index:
            if len(pq) < k:
                heappush(pq, ind)
            elif len(pq) >= k and pq[0] < ind:
                heappushpop(pq, ind)
        
        cnt_set = set(pq)

        return [ key for key, val in cnt.items() if val in cnt_set]

# @lc code=end

