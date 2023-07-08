/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] 反转链表 II
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "common_types/LinkedList/LinkedList.h"

using namespace std;
using ListNode = LinkedListNode<int>;

// @lc code=start
class Solution {
 public:
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* dummyNode = new ListNode(-1);
    dummyNode->next = head;
    ListNode* pre = dummyNode;
    for (int i = 0; i < left - 1; i++) {
      pre = pre->next;
    }
    ListNode* cur = pre->next;
    ListNode* next = nullptr;
    for (int i = 0; i < right - left; i++) {
      next = cur->next;
      cur->next = next->next;
      next->next =
          pre->next;  // ! here, from second iteration the `cur` != `pre->next`.
      pre->next = next;
    }
    ListNode* ret = dummyNode->next;
    delete dummyNode;
    return ret;
  }
};
// @lc code=end

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  ListNode* head = BuildLinkedlist<int>(v);
  showLinkedList<int>(head);
  int left = 2, right = 4;
  Solution sol;
  ListNode* r = sol.reverseBetween(head, left, right);
  showLinkedList<int>(r);
  DestroyLinkedlist<int>(head);
  return 0;
}
