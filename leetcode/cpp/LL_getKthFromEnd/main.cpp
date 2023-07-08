/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 完全二叉树的节点个数
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
  ListNode* getKthFromEnd(ListNode* head, int k) {
    if (!head) return nullptr;
    if (!k) return nullptr;
    ListNode *slow = head, *fast = head;
    int count = 0;
    while (fast != nullptr && count < k) {
      fast = fast->next;
      count++;
    }
    if (!fast) return head;

    for (; fast->next != nullptr; slow = slow->next, fast = fast->next)
      ;
    return slow->next;
  }
};
// @lc code=end

int main() {
  Solution s;
  vector<int> v = {1, 2, 3, 4, 5};
  ListNode* head = BuildLinkedlist<int>(v);
  showLinkedList<int>(head);
  ListNode* k = s.getKthFromEnd(head, 2);
  showLinkedList<int>(k);
  DestroyLinkedlist<int>(head);
  return 0;
}
