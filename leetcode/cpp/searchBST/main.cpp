/*
 * @lc app=leetcode.cn id=700 lang=cpp
 *
 * [700] 二叉搜索树中的搜索
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
  TreeNode* searchBST(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    if (val < root->val) return searchBST(root->left, val);
    if (val > root->val) return searchBST(root->right, val);
    return nullptr;
  }
};
// @lc code=end

int main() {
  const int null = BinaryTree::null<int>();
  vector<int> a{4, 2, 7, 1, 3};
  TreeNode* root = BuildBinaryTree<int>(a);
  showBinaryTree<int>(root);
  int val = 12;
  Solution sol;
  TreeNode* v = sol.searchBST(root, val);
  showBinaryTree<int>(v);
  return 0;
}
