/*
 * @lc app=leetcode.cn id=230 lang=cpp
 *
 * [230] 二叉搜索树中第K小的元素
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
  int find(TreeNode *root, int &k) {
    if (!root) return 0;
    int top_k_from_left = find(root->left, k);
    // This is mean that we are already full use of k.
    // so the top k will be the left branch.
    if (k == 0) return top_k_from_left;
    k -= 1;
    // if k == 1 this means that the root is the answer.
    if (k == 0) return root->val;
    // we can continue to search in the right branch.
    // the k is not initalized value.
    return find(root->right, k);
  }

  int kthSmallest(TreeNode *root, int k) { return find(root, k); }
};
// @lc code=end

int main() {
  const int null = BinaryTree::null<int>();
  vector<int> tr = {5, 3, 6, 2, 4, null, null, 1};
  int k = 3;
  TreeNode *root = BuildBinaryTree<int>(tr);
  Solution sol;
  auto v = sol.kthSmallest(root, k);
  fmt::print("{}\n", v);
  showBinaryTree<int>(root);
  return 0;
}
