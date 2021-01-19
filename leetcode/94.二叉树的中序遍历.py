#
# @lc app=leetcode.cn id=94 lang=python3
#
# [94] 二叉树的中序遍历
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
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        res = []
        sta = [("w", root)]

        while len(sta) != 0:
            color, node = sta.pop()
            if node is None:
                continue
            if color == "w":
                sta.append(("w", node.right))
                sta.append(("g", node))
                sta.append(("w", node.left))
            else:
                res.append(node.val)

        return res

# @lc code=end
