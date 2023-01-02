#ifndef BINARYTREENODE_H_
#define BINARYTREENODE_H_

template <typename T>
class BinaryTreeNode{
public:
  BinaryTreeNode() = delete;
  explicit BinaryTreeNode(T item): data(item), left(nullptr), right(nullptr){};
  ~BinaryTreeNode() = default;
  T data;
  BinaryTreeNode *left;
  BinaryTreeNode *right;
};

#endif