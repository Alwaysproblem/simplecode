#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <typename T>
class LinkedListNode {
 public:
  LinkedListNode() : val(0), next(nullptr){};
  explicit LinkedListNode(T item) : val(item), next(nullptr){};
  ~LinkedListNode() = default;
  T val;
  LinkedListNode<T> *next;
};

template <typename T>
void showLinkedList(LinkedListNode<T> *node) {
  for (; node != nullptr; node = node->next) {
    if (node->next == nullptr) {
      std::cout << node->val;
    } else {
      std::cout << node->val << " -> ";
    }
  }
  std::cout << std::endl;
}

template <typename T>
LinkedListNode<T> *BuildLinkedlist(std::vector<T> &array) {
  LinkedListNode<T> *head = new LinkedListNode<T>();
  LinkedListNode<T> *cur = head;
  for (T ival : array) {
    cur->next = new LinkedListNode<T>(ival);
    cur = cur->next;
  }

  cur = head;
  head = head->next;
  delete cur;
  cur = nullptr;
  return head;
}

template <typename T>
LinkedListNode<T> *BuildLinkedlist(std::vector<T> &&array) {
  std::vector<T> tmp = array;
  return BuildLinkedlist<T>(tmp);
}

template <typename T>
void DestroyLinkedlist(LinkedListNode<T> *head) {
  if (head == nullptr) return;
  DestroyLinkedlist<T>(head->next);
  delete head;
  head = nullptr;
}

template <typename T>
LinkedListNode<T> *BuildCycleLinkedlist(std::vector<T> &array, int pos) {
  LinkedListNode<T> *head = new LinkedListNode<T>();
  LinkedListNode<T> *cur = head;
  int idx = 0;
  LinkedListNode<T> *cycle_pos = nullptr;
  for (T ival : array) {
    cur->next = new LinkedListNode<T>(ival);
    if (pos >= 0 && idx == pos + 1) {
      cycle_pos = cur;
    }
    cur = cur->next;
    idx++;
  }
  if (cycle_pos) {
    cur->next = cycle_pos;
  }
  cur = head;
  head = head->next;
  delete cur;
  cur = nullptr;
  return head;
}

template <typename T>
LinkedListNode<T> *BuildCycleLinkedlist(std::vector<T> &&array, int pos) {
  std::vector<T> tmp = array;
  return BuildCycleLinkedlist(tmp, pos);
}

template <typename T>
LinkedListNode<T> *DetectCycle(LinkedListNode<T> *head) {
  if (head == nullptr) return nullptr;
  LinkedListNode<T> *slow = head, *fast = head;
  while (slow->next != nullptr && fast->next != nullptr &&
         fast->next->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      break;
    }
  }

  if (slow->next == nullptr) return nullptr;
  if (fast->next == nullptr) return nullptr;
  if (fast->next->next == nullptr) return nullptr;

  LinkedListNode<T> *res = head;
  while (res != slow) {
    res = res->next;
    slow = slow->next;
  }
  return res;
}

template <typename T>
void DestroyCycleLinkedlist(LinkedListNode<T> *head) {
  if (head == nullptr) return;
  LinkedListNode<T> *cycle_start = DetectCycle<T>(head);
  if (cycle_start != nullptr) cycle_start->next = nullptr;
  return DestroyLinkedlist<T>(head);
}

#endif
