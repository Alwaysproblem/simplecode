/*
 * @lc app=leetcode.cn id=* lang=cpp
 *
 * [*] ******
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

// @lc code=end

int main() {
  const int null = BinaryTree::null<int>();
  vector<int> a{3, 9, 20, null, null, 15, 7};
  TreeNode *root = BuildBinaryTree<int>(a);
  showBinaryTree<int>(root);
  return 0;
}
