/*
 * @lc app=leetcode.cn id=450 lang=cpp
 *
 * [450] 删除二叉搜索树中的节点
 * title: delete-node-in-a-bst
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
  TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return root;
    if (root->val == key) {
      if (!root->left && !root->right) return nullptr;
      if (!root->left && root->right) return root->right;
      if (!root->right && root->left) return root->left;
      TreeNode* min_n = root->right;
      while (min_n->left != nullptr) min_n = min_n->left;
      root->val = min_n->val;
      root->right = deleteNode(root->right, min_n->val);
    } else if (root->val > key) {
      root->left = deleteNode(root->left, key);
    } else if (root->val < key) {
      root->right = deleteNode(root->right, key);
    }
    return root;
  }
};
// @lc code=end

int main() {
  const int null = BinaryTree::null<int>();
  vector<int> a{5, 3, 6, 2, 4, null, 7};
  TreeNode* root = BuildBinaryTree<int>(a);
  showBinaryTree<int>(root);
  int key = 3;
  Solution sol;
  TreeNode* r = sol.deleteNode(root, key);
  showBinaryTree<int>(r);
  return 0;
}
