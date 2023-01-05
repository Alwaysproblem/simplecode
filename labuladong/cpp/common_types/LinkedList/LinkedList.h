#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <typename T>
class LinkedListNode{
public:
  LinkedListNode() = delete;
  explicit LinkedListNode(T item): val(item), next(nullptr){};
  ~LinkedListNode() = default;
  T val;
  LinkedListNode *next;
};

#endif