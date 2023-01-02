#include <iostream>
#include <map>
#include <vector>
#include "common_types/TreeNode/BinaryTreeNode.h"

using namespace std;

template<typename T>
void printTree(BinaryTreeNode<T> *head){
  if (nullptr == head) return;
  printTree<T>(head->left);
  cout << head->data << " ";
  printTree<T>(head->right);
}

int main()
{
  BinaryTreeNode<int> n1(1);
  BinaryTreeNode<int> n2(2);
  BinaryTreeNode<int> n3(3);
  BinaryTreeNode<int> n4(4);
  n1.left = &n2;
  n1.right = &n3;
  n2.left = &n4;
  BinaryTreeNode<int> *head = &n1;
  printTree<int>(head);
}
