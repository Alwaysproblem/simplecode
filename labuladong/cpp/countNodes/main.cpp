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

template <typename... T>
void debug_recursive(string format, int level, T&&... args) {
  string indent = "    ";
  for (int i = 0; i <= level; i++) {
    fmt::print("{}", indent);
  }
  fmt::print(format, args...);
}

class Solution {
 public:
  int level = 0;
  int countNodes(TreeNode* root) {
    if (!root) return 0;
    int hl = 0;
    int hr = 0;
    TreeNode* cur = root;
    for (hl = 0; cur; cur = cur->left, hl++);

    cur = root;
    for (hr = 0; cur; cur = cur->right, hr++);
    if (hr == hl)
      return (int) pow(2, hr) - 1;

    return countNodes(root->left) + countNodes(root->right) + 1;
  }
};

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
