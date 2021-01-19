#
# @lc app=leetcode.cn id=129 lang=python3
#
# [129] 求根到叶子节点数字之和
#
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# @lc code=start
# Definition for a binary tree node.

class Solution:
    def sumNumbers(self, root: TreeNode) -> int:
        if root is None:
            return 0
        S = []
        def helper(root):
            if root.left is None and  root.right is None:
                S.append(root.val)
                return
            if root.left is not None:
                root.left.val = root.val * 10 + root.left.val
                helper(root.left)
            if root.right is not None:
                root.right.val = root.val * 10 + root.right.val
                helper(root.right)
        
        helper(root)
        return sum(S)
# @lc code=end

if __name__ == "__main__":
    root = TreeNode(0)
    root.left=TreeNode(1)
    # root.left.left=TreeNode(5)
    # root.left.right=TreeNode(1)
    # root.right=TreeNode(0)
    print(Solution().sumNumbers(root))
