/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
 * title: lowest-common-ancestor-of-a-binary-tree
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

TreeNode *findNode(TreeNode *root, int val) {
  if (!root) return nullptr;
  if (root->val == val) return root;
  TreeNode *l = nullptr, *r = nullptr;
  if (root->left) l = findNode(root->left, val);
  if (root->right) r = findNode(root->right, val);
  return l != nullptr ? l : r;
}

// @lc code=start
class Solution {
 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (!root) return nullptr;
    if (root == p) return p;
    if (root == q) return q;

    TreeNode *lca_l = nullptr, *lca_r = nullptr;
    if (root->left) lca_l = lowestCommonAncestor(root->left, p, q);
    if (root->right) lca_r = lowestCommonAncestor(root->right, p, q);

    if (lca_l == nullptr) return lca_r;
    if (lca_r == nullptr) return lca_l;
    if (lca_r == nullptr && lca_l == nullptr) return nullptr;
    return root;
  }
};
// @lc code=end

int main() {
  const int null = BinaryTree::null<int>();
  vector<int> a{3, 5, 1, 6, 2, 0, 8, null, null, 7, 4};
  int val_p = 0;
  int val_q = 8;
  TreeNode *root = BuildBinaryTree<int>(a);
  TreeNode *p = findNode(root, val_p);
  TreeNode *q = findNode(root, val_q);
  showBinaryTree<int>(root);
  Solution sol;
  TreeNode *lca = sol.lowestCommonAncestor(root, p, q);
  showBinaryTree<int>(lca);
  return 0;
}
