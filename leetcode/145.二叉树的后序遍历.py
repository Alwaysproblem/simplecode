#
# @lc app=leetcode.cn id=145 lang=python3
#
# [145] 二叉树的后序遍历
#

# @lc code=start
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        
        sta = [("w", root)]
        res = []
        
        while sta:

            color, node = sta.pop()
            if node is None:
                continue

            if color == "w":
                sta.append(("g", node))
                sta.append(("w", node.right))
                sta.append(("w", node.left))
            else:
                res.append(node.val)
        return res

# @lc code=end

