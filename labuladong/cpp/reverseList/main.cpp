#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "common_types/LinkedList/LinkedList.h"

using namespace std;
using ListNode = LinkedListNode<int>;

class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) {
      return head;
    }
    ListNode* tail = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return tail;
  }

  ListNode* tail_ptr = nullptr;
  ListNode* reverseList1(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) {
      tail_ptr = head;
      return head;
    }
    ListNode* tail = reverseList(head->next);
    tail->next = head;
    head->next = nullptr;
    return head;
  }

  ListNode* reverseList2(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) {
      return head;
    }
    ListNode *cur = head;
    ListNode *nex = nullptr;
    ListNode *pre = nullptr;
    while (cur->next){
      nex = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nex;
    }
    cur->next = pre;
    return cur;
  }
};

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  ListNode* head = BuildLinkedlist<int>(v);
  showLinkedList<int>(head);
  Solution sol;
  ListNode* r = sol.reverseList2(head);
  showLinkedList<int>(r);
  DestroyLinkedlist<int>(head);
  // DestroyLinkedlist<int>(r);
  return 0;
}
