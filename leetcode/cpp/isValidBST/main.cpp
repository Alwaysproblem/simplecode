/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] 验证二叉搜索树
 * title: validate-binary-search-tree
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "common_types/TreeNode/BinaryTreeNode.h"

using namespace std;
using TreeNode = BinaryTree::BinaryTreeNode<int>;
using BinaryTree::BuildBinaryTree;
using BinaryTree::showBinaryTree;

// @lc code=start
class Solution {
 public:
  bool isValidBST_helper(TreeNode *root, TreeNode *min, TreeNode *max) {
    if (!root) return true;
    if (min && min->val >= root->val) return false;
    if (max && max->val <= root->val) return false;
    return isValidBST_helper(root->left, min, root) &&
           isValidBST_helper(root->right, root, max);
  }
  bool isValidBST(TreeNode *root) {
    return isValidBST_helper(root, nullptr, nullptr);
  }
};
// @lc code=end

int main() {
  const int null = BinaryTree::null<int>();
  vector<int> a{5, 4, 6, null, null, 3, 7};
  // vector<int> a{3, 7, 15, null, null, 9, 20};
  TreeNode *root = BuildBinaryTree<int>(a);
  showBinaryTree<int>(root);
  Solution sol;
  bool v = sol.isValidBST(root);
  fmt::print("{}\n", v);
  return 0;
}
