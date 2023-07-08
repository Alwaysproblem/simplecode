/*
 * @lc app=leetcode.cn id=234 lang=cpp
 *
 * [234] 回文链表
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
  ListNode *comp = nullptr;
  int f = 0, b = 0;
  ListNode *reversed(ListNode *head, int b) {
    if (!head->next) return head;
    b++;
    ListNode *tail = reversed(head->next, b);
    if (!tail) return nullptr;
    if (f > b) return tail;
    if (comp->val != tail->val) return nullptr;
    comp = comp->next;
    f++;
    return head;
  }

  bool isPalindrome(ListNode *head) {
    comp = head;
    ListNode *p = reversed(head, 0);
    if (!p) return false;
    return true;
  }
};
// @lc code=end

int main() {
  vector<int> v = {1, 2, 4, 3, 2, 1};
  ListNode *head = BuildLinkedlist<int>(v);
  showLinkedList<int>(head);
  Solution sol;
  bool r = sol.isPalindrome(head);
  fmt::print("{}\n", r);
  DestroyLinkedlist<int>(head);
  return 0;
}
