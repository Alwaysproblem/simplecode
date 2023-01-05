#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <typename T>
class LinkedListNode
{
public:
  LinkedListNode() = delete;
  explicit LinkedListNode(T item) : val(item), next(nullptr){};
  ~LinkedListNode() = default;
  T val;
  LinkedListNode *next;
};

template <typename T>
void showLinkedList(LinkedListNode<T> *node)
{
  for (; node != nullptr; node = node->next)
  {
    if (node->next == nullptr)
    {
      std::cout << node->val;
    }
    else
    {
      std::cout << node->val
                << " -> ";
    }
  }
  std::cout << std::endl;
}

#endif
