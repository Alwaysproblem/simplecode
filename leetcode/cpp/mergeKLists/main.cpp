/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并 K 个升序链表
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "common_types/LinkedList/LinkedList.h"

using namespace std;
using ListNode = LinkedListNode<int>;

// @lc code=start
struct Compare {
  bool operator()(const pair<int, int> a, const pair<int, int> b) {
    return a.first > b.first;
  }
};

// Use the heap to find the min value among k values.
class Solution {
 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (!lists.size()) return nullptr;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    ListNode dummy(-20000);
    vector<ListNode*> ptrs(lists);
    for (int i = 0; i < lists.size(); i++) {
      if (ptrs[i]) pq.push(make_pair(ptrs[i]->val, i));
    }

    ListNode* construct_ptr = &dummy;

    while (!pq.empty()) {
      auto cur = pq.top();
      pq.pop();
      construct_ptr->next = new ListNode(cur.first);
      construct_ptr = construct_ptr->next;
      if (ptrs[cur.second]) {
        ptrs[cur.second] = ptrs[cur.second]->next;
        if (ptrs[cur.second])
          pq.push(make_pair(ptrs[cur.second]->val, cur.second));
      }
    }
    return dummy.next;
  }
};
// @lc code=end

int main() {
  vector<vector<int>> inp = {{}};
  // vector<vector<int>> inp = {{1, 4, 5}, {1, 3, 4}, {2, 6}};
  vector<ListNode*> lists = {};
  for (auto& i : inp) {
    lists.emplace_back(BuildLinkedlist<int>(i));
  }
  Solution sol;
  auto head = sol.mergeKLists(lists);
  showLinkedList<int>(head);
  DestroyLinkedlist<int>(head);
  return 0;
}
