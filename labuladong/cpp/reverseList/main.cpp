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
  // method 1
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

  // method 2
  // `ListNode* &tail_ptr` This is the reference of ListNode ptr.
  // with this `tail_ptr = head;` can be worked or every time the code 
  // use the `tail_ptr` will be a copy of value not reference.
  ListNode* reverseList1_helper(ListNode* head, ListNode* &tail_ptr) {
    if (!head) return nullptr;
    if (!head->next) {
      tail_ptr = head;
      return head;
    }
    ListNode* tail = reverseList1_helper(head->next, tail_ptr);
    tail->next = head;
    head->next = nullptr;
    return head;
  }

  ListNode* reverseList1(ListNode* head){
    ListNode* tail_ptr = nullptr;
    reverseList1_helper(head, tail_ptr);
    return tail_ptr;
  }


  // method 3
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
  ListNode* r = sol.reverseList(head);
  showLinkedList<int>(r);
  DestroyLinkedlist<int>(head);
  // DestroyLinkedlist<int>(r);
  return 0;
}
