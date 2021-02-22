#
# @lc app=leetcode.cn id=199 lang=python3
#
# [199] 二叉树的右视图
#
from typing import List
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# @lc code=start
# Definition for a binary tree node.
class Solution:
    def rightSideView(self, root: TreeNode) -> List[int]:
        if root is None:
            return []
        queue = [(root, 0)]
        res = []

        def extend(cur, height):
            return (cur.left, height + 1,), (cur.right, height + 1, )
        
        while len(queue) != 0:
            cur, h = queue.pop(0)
            if len(queue) == 0 or queue[0][1] != h:
                res.append(cur.val)
            (l, hl), (r, hr) = extend(cur, h)
            if l is not None:
                queue.append((l, hl))
            if r is not None:
                queue.append((r, hr))

        return res
# @lc code=end

