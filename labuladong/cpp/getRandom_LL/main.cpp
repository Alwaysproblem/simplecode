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
  int getRandom(ListNode *head) {
    int i = 0, res = 0;
    for (ListNode *cur = head; cur != nullptr; cur = cur->next) {
      i ++;
      if (0 == (rand() % i)) {
        res = cur->val;
      }
    }
    return res;
  }
  vector<int> getKRandom(ListNode *head, int k) {
    vector<int> res(k);
    ListNode *p = head;
    for (int i = 0; i < k; i++){
      res[i] = p->val;
      p = p->next;
    }

    int i = 0, j = 0;
    for (ListNode *cur = head; cur != nullptr; cur = cur->next) {
      i ++;
      j = rand() % i;
      if (k > j) {
        res[j++] = cur->val;
      }
    }
    return res;
  }
};

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  ListNode *head = BuildLinkedlist<int>(v);
  showLinkedList<int>(head);
  Solution sol;
  int r = sol.getRandom(head);
  fmt::print("{}\n", r);
  r = sol.getRandom(head);
  fmt::print("{}\n", r);
  r = sol.getRandom(head);
  fmt::print("{}\n", r);
  r = sol.getRandom(head);
  fmt::print("{}\n", r);
  int k = 3;
  vector<int> res = sol.getKRandom(head, k);
  fmt::print("{}\n", res);
  res = sol.getKRandom(head, k);
  fmt::print("{}\n", res);
  res = sol.getKRandom(head, k);
  fmt::print("{}\n", res);
  res = sol.getKRandom(head, k);
  fmt::print("{}\n", res);
  DestroyLinkedlist<int>(head);
  return 0;
}
