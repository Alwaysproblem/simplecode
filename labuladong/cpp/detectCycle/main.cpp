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
  ListNode *detectCycle(ListNode *head) {
    if (head == nullptr) return nullptr;
    ListNode *slow = head, *fast = head;
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

    ListNode *res = head;
    while (res != slow) {
      res = res->next;
      slow = slow->next;
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> v = {1, 2, 3, 4, 5};
  ListNode *head = BuildCycleLinkedlist<int>(v, 1);
  // showLinkedList<int>(head);
  fmt::print("the head of cycle is {}\n",
             sol.detectCycle(head) == nullptr ? -1 : head->val);
  DestroyCycleLinkedlist<int>(head);
  showLinkedList<int>(head);
  return 0;
}
