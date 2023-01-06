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
using BinaryTree::BuildBinaryTree;
using BinaryTree::showBinaryTree;

class Solution
{
public:
  int minDepth(TreeNode *root)
  {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;

    queue<TreeNode*> q;
    q.push(root);
    TreeNode* cur = nullptr;

    int depth = 0;
    while (!q.empty())
    {
      int sz = q.size();
      for (int ix = 0; ix < sz; ++ix){
        cur = q.front();
        q.pop();
        if (cur->left == nullptr && cur->right == nullptr){
          return depth + 1;
        }
        if (cur->left != nullptr) q.push(cur->left);
        if (cur->right != nullptr) q.push(cur->right);

      }
      depth ++;
    }
    return depth;
  }
};

int main(int argc, char **argv)
{
  const int null = BinaryTree::null<int>();
  auto tree = BuildBinaryTree<int>({2,null,3,null,4,null,5,null,6});
  // auto tree = BuildBinaryTree<int>({3,9,20,null,null,15,7});
  showBinaryTree<int>(tree);

  Solution solution;
  auto minDepth = solution.minDepth(tree);
  fmt::print("The min depth is: {}\n", minDepth);

  return 0;
}
