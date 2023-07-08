/*
 * @lc app=leetcode.cn id=297 lang=cpp
 *
 * [297] 二叉树的序列化与反序列化
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
vector<string> split(string str, string delimiter = " ") {
  vector<string> tokens;
  size_t start = 0, end = 0;
  while ((end = str.find(delimiter, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delimiter.length();
  }
  return tokens;
}

class Codec {
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode *root) {
    queue<TreeNode *> q;

    q.push(root);
    TreeNode *cur = nullptr;
    string serialize_str = "";

    while (!q.empty()) {
      int sz = q.size();
      for (int i = 0; i < sz; i++) {
        cur = q.front();
        q.pop();
        if (cur == nullptr) {
          serialize_str += "null, ";
          continue;
        }
        serialize_str += to_string(cur->val);
        serialize_str += ", ";
        q.push(cur->left);
        q.push(cur->right);
      }
    }
    return serialize_str;
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data) {
    if (data == "") return nullptr;
    vector<string> tokens = split(data, string(", "));
    queue<TreeNode *> q;
    int idx = 0;
    if (tokens[idx] == "null") return nullptr;
    TreeNode *root = new TreeNode(stoi(tokens[idx]));
    q.push(root);
    TreeNode *cur = nullptr;

    while (!q.empty() && idx < tokens.size()) {
      cur = q.front();
      q.pop();

      if (cur == nullptr) {
        continue;
      }

      idx++;
      if (tokens[idx] == "null")
        cur->left = nullptr;
      else
        cur->left = new TreeNode(stoi(tokens[idx]));
      q.push(cur->left);
      idx++;
      if (tokens[idx] == "null")
        cur->right = nullptr;
      else
        cur->right = new TreeNode(stoi(tokens[idx]));
      q.push(cur->right);
    }
    return root;
  }
};
// @lc code=end

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main() {
  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(9);
  root->right = new TreeNode(20);
  root->right->left = new TreeNode(15);
  root->right->right = new TreeNode(7);
  showBinaryTree<int>(root);
  Codec c;
  string s = c.serialize(root);
  fmt::print("The Serialized BinaryTree: {}\n", s);
  string data = "3, 9, 20, null, null, 15, 7, null, null, null, null, ";
  TreeNode *root_d = c.deserialize(data);
  showBinaryTree<int>(root_d);
  return 0;
}
