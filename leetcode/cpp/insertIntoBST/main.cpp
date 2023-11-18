/*
 * @lc app=leetcode.cn id=701 lang=cpp
 *
 * [701] 二叉搜索树中的插入操作
 * title: insert-into-a-binary-search-tree
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
  TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (root->val == val) return root;
    if (val < root->val)
      root->left = insertIntoBST(root->left, val);
    else
      root->right = insertIntoBST(root->right, val);
    return root;
  }
};
// @lc code=end

int main() {
  const int null = BinaryTree::null<int>();
  vector<int> a{5, 1, 7};
  TreeNode* root = BuildBinaryTree<int>(a);
  showBinaryTree<int>(root);
  int val = 6;
  Solution sol;
  TreeNode* r = sol.insertIntoBST(root, val);
  showBinaryTree<int>(root);
  return 0;
}
