#
# @lc app=leetcode.cn id=113 lang=python3
#
# [113] 路径总和 II
#
from typing import List
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
# @lc code=start
# Definition for a binary tree node.

class Solution:
    def pathSum(self, root: TreeNode, Sum: int) -> List[List[int]]:
        com = []
        coms = []

        def backtrace(root, com):
            if root is None:
                return

            if not root.left and not root.right:
                c = com.copy()
                c.append(root.val)
                if sum(c) == Sum:
                    coms.append(c)
                    return

            com.append(root.val)
            backtrace(root.left, com)
            backtrace(root.right, com)
            com.pop()

        backtrace(root, com)
        return coms
# @lc code=end


if __name__ == "__main__":
    root = TreeNode(5)
    root.left=TreeNode(4)
    root.right=TreeNode(8)
    root.right.left=TreeNode(13)
    root.right.right=TreeNode(4)
    root.right.right.left=TreeNode(5)
    root.right.right.right=TreeNode(1)
    root.left.left=TreeNode(11)
    root.left.left.left=TreeNode(7)
    root.left.left.right=TreeNode(2)
    print(Solution().pathSum(root, 22))
