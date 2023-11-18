/*
 * @lc app=leetcode.cn id=* lang=cpp
 *
 * [*] ******
 * title: ******
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

// @lc code=end

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  ListNode *head = BuildLinkedlist<int>(v);
  showLinkedList<int>(head);
  DestroyLinkedlist<int>(head);
  return 0;
}
