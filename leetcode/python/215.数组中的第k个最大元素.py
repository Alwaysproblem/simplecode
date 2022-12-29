#
# @lc app=leetcode.cn id=215 lang=python3
#
# [215] 数组中的第K个最大元素
#
from typing import *

# @lc code=start
from heapq import *
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        pq = []
        for i in nums:
            if len(pq) >= k and pq[0] < i:
                heappushpop(pq, i)
            elif len(pq) < k :
                heappush(pq, i)
        return heappop(pq)
# @lc code=end

if __name__ == "__main__":
    print(Solution().findKthLargest([1,2,4,3], 3))