from typing import List, Tuple, Set

class BiLinkedListNode:
    def __init__(self, val=0, next = None, prev = None):
        self.val = val
        self.next = next
        self.prev = prev

class LinkedListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class BinaryTreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.children: List[TreeNode] = []

__all__ = [
  List,
  Tuple,
  Set,
  BiLinkedListNode,
  LinkedListNode,
  BinaryTreeNode,
  TreeNode,
]