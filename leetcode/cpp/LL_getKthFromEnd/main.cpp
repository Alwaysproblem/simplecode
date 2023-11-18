/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
 * title: remove-nth-node-from-end-of-list
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
  ListNode* removeNthFromEnd(ListNode* head, int k) {
    if (!head) return nullptr;
    if (!k) return nullptr;
    ListNode *slow = head, *fast = head;
    int count = 0;
    while (fast != nullptr && count < k) {
      fast = fast->next;
      count++;
    }
    if (!fast) {
      if (count == k) {
        ListNode* del = head;
        head = head->next;
        delete del;
        return head;
      }
      return head;
    };

    for (; fast->next != nullptr; slow = slow->next, fast = fast->next)
      ;
    ListNode* del = slow->next;
    slow->next = slow->next->next;
    delete del;
    return head;
  }
};
// @lc code=end

int main() {
  Solution s;
  vector<int> v = {1};
  ListNode* head = BuildLinkedlist<int>(v);
  showLinkedList<int>(head);
  ListNode* k = s.removeNthFromEnd(head, 1);
  showLinkedList<int>(k);
  DestroyLinkedlist<int>(k);
  return 0;
}
