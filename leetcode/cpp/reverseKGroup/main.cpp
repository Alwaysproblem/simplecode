/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
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
  ListNode* reverse(ListNode* head, ListNode* target) {
    ListNode *pre = nullptr, *cur = head, *nxt = head;
    while (cur != target) {
      nxt = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nxt;
    }
    return pre;
  }
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head) return head;
    ListNode* cur = nullptr;
    int i = 0;
    for (cur = head; cur != nullptr && i < k; cur = cur->next, i++)
      ;
    if (i < k) return head;
    ListNode* tail = reverseKGroup(cur, k);
    ListNode* new_head = reverse(head, cur);
    head->next = tail;
    return new_head;
  }
};
// @lc code=end

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  int k = 2;
  ListNode* head = BuildLinkedlist<int>(v);
  showLinkedList<int>(head);
  Solution sol;
  ListNode* r = sol.reverseKGroup(head, k);
  showLinkedList<int>(r);
  DestroyLinkedlist<int>(head);
  return 0;
}
