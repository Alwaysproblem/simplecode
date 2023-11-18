/*
 * @lc app=leetcode.cn id=337 lang=cpp
 *
 * [337] 打家劫舍 III
 * title: house-robber-iii
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
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
  unordered_map<TreeNode*, int> mem{};
  int backtrack(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return root->val;
    if (mem.count(root)) return mem[root];

    // if not choose root
    int max_val = 0;
    max_val = max(max_val, backtrack(root->left) + backtrack(root->right));

    // if choose root;
    int sums = 0;
    if (root->left) {
      sums += backtrack(root->left->left) + backtrack(root->left->right);
    }
    if (root->right) {
      sums += backtrack(root->right->left) + backtrack(root->right->right);
    }
    sums += root->val;

    // find max value
    max_val = max(max_val, sums);
    mem[root] = max_val;
    return max_val;
  }
  int rob(TreeNode* root) { return backtrack(root); }
};
// @lc code=end

int main() {
  const int null = BinaryTree::null<int>();
  vector<int> a{3, 4, 5, 1, 3, null, 1};
  TreeNode* root = BuildBinaryTree<int>(a);
  showBinaryTree<int>(root);
  Solution sol;
  int v = sol.rob(root);
  fmt::print("{}\n", v);
  return 0;
}
