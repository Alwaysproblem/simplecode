/*
 * @lc app=leetcode.cn id=222 lang=cpp
 *
 * [222] 完全二叉树的节点个数
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "common_types/TreeNode/BinaryTreeNode.h"
#include "utils/debug_recursive.hpp"

using namespace std;
using TreeNode = BinaryTree::BinaryTreeNode<int>;
using BinaryTree::BuildBinaryTree;
using BinaryTree::showBinaryTree;

// @lc code=start
class Solution {
 public:
  int level = 0;
  int countNodes(TreeNode* root) {
    if (!root) return 0;
    int hl = 0;
    int hr = 0;
    TreeNode* cur = root;
    for (hl = 0; cur; cur = cur->left, hl++)
      ;

    cur = root;
    for (hr = 0; cur; cur = cur->right, hr++)
      ;
    if (hr == hl) return (int)pow(2, hr) - 1;

    return countNodes(root->left) + countNodes(root->right) + 1;
  }
};
// @lc code=end

int main() {
  const int null = BinaryTree::null<int>();
  vector<int> a{1, 2, 3, 4, 5, 6};
  TreeNode* root = BuildBinaryTree<int>(a);
  showBinaryTree<int>(root);
  Solution sol;
  fmt::print("\n");
  int v = sol.countNodes(root);
  fmt::print("{}\n", v);
  return 0;
}
