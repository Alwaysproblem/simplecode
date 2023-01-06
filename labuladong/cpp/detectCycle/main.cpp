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
    ListNode *slow = head, *fast = head;
    while (slow->next != nullptr && slow->next->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        break;
      }
    }
    if (slow->next == nullptr) return nullptr;
    ListNode *res = head;
    while (res != slow) {
      res = res->next;
      slow = slow->next;
    }
    return res;
  }
};

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  ListNode *head = BuildLinkedlist<int>(v);
  // ListNode *head = BuildCycleLinkedlist<int>(v, 1);
  showLinkedList<int>(head);
  DestroyLinkedlist<int>(head);
  showLinkedList<int>(head);
  return 0;
}
