#
# @lc app=leetcode.cn id=144 lang=python3
#
# [144] 二叉树的前序遍历
#
from typing import *
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
# @lc code=start
# Definition for a binary tree node.
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        
        stack = [("w", root)]
        res = []

        while len(stack) != 0:
            clr, cur = stack.pop()

            if cur is None:
                continue
        
            if clr == "w":
                stack.append(("w", cur.right))
                stack.append(("w", cur.left))
                stack.append(("g", cur))
            
            else:
                res.append(cur.val)
        
        return res
# @lc code=end

