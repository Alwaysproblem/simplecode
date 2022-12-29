#
# @lc app=leetcode.cn id=147 lang=python3
#
# [147] 对链表进行插入排序
#
from typing import *
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
# @lc code=start
# Definition for singly-linked list.
class Solution:
    def insertionSortList(self, head: ListNode) -> ListNode:

        def insert(node, pos):
            tmp = pos.next
            pos.next = node
            node.next = tmp
        
        ans = ListNode(float("-inf"))

        while head:
            callme = head.next
            cur = ans

            while cur.next and cur.next.val <= head.val:
                cur = cur.next
            
            insert(head, cur)
            head = callme
        
        return ans.next

# @lc code=end

