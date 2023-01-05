#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include "common_types/TreeNode/BinaryTreeNode.h"

using namespace std;
using TreeNode = BinaryTree::BinaryTreeNode<int>;
using BinaryTree::showBinaryTree;
using BinaryTree::BuildBinaryTree;


int main()
{
  const int null = BinaryTree::null<int>();
  vector<int> a{3, 9, 20, null, null, 15, 7};
  TreeNode *root = BuildBinaryTree<int>(a);
  showBinaryTree<int>(root);
  return 0;
}
