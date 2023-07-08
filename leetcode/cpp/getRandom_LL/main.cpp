/*
 * @lc app=leetcode.cn id=382 lang=cpp
 *
 * [382] 链表随机节点
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
  ListNode *head_;
  Solution(ListNode *head) : head_(head) {}

  int getRandom(ListNode *cur_head = nullptr) {
    if (!cur_head) {
      cur_head = head_;
    }
    int i = 0, res = 0;
    for (ListNode *cur = cur_head; cur != nullptr; cur = cur->next) {
      i++;
      if (0 == (rand() % i)) {
        res = cur->val;
      }
    }
    return res;
  }
  vector<int> getKRandom(int k = 1, ListNode *cur_head = nullptr) {
    if (!cur_head) {
      cur_head = head_;
    }
    vector<int> res(k);
    ListNode *p = cur_head;
    for (int i = 0; i < k; i++) {
      res[i] = p->val;
      p = p->next;
    }

    int i = 0, j = 0;
    for (ListNode *cur = cur_head; cur != nullptr; cur = cur->next) {
      i++;
      j = rand() % i;
      if (k > j) {
        res[j++] = cur->val;
      }
    }
    return res;
  }
};
// @lc code=end

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  ListNode *head = BuildLinkedlist<int>(v);
  showLinkedList<int>(head);
  Solution sol(head);
  int r = sol.getRandom();
  fmt::print("{}\n", r);
  r = sol.getRandom();
  fmt::print("{}\n", r);
  r = sol.getRandom();
  fmt::print("{}\n", r);
  r = sol.getRandom();
  fmt::print("{}\n", r);
  int k = 3;
  vector<int> res = sol.getKRandom(k);
  fmt::print("{}\n", res);
  res = sol.getKRandom(k);
  fmt::print("{}\n", res);
  res = sol.getKRandom(k);
  fmt::print("{}\n", res);
  res = sol.getKRandom(k);
  fmt::print("{}\n", res);
  DestroyLinkedlist<int>(head);
  return 0;
}
