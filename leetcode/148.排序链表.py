#
# @lc app=leetcode.cn id=148 lang=python3
#
# [148] 排序链表
#
from typing import *
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
# @lc code=start
# Definition for singly-linked list.
class Solution:
    def sortList(self, head: ListNode) -> ListNode:

        def sortFun(head, tail):
            if not head:
                return head
            
            if head.next == tail:
                head.next = None
                return head
            # note cut the linked list
            slow = fast = head

            while fast != tail:
                fast = fast.next
                slow = slow.next
                if fast != tail:
                    fast = fast.next
            mid = slow

            return merge(sortFun(head, mid), sortFun(mid, tail))

        def merge(head1, head2):
            dummy = ListNode(float("inf"))
            tmp, tmp1, tmp2 = dummy, head1, head2

            while tmp1 and tmp2:
                if tmp1.val <= tmp2.val:
                    tmp.next = tmp1
                    tmp1 = tmp1.next
                else:
                    tmp.next = tmp2
                    tmp2 = tmp2.next

                tmp = tmp.next
            
            if tmp1:
                tmp.next = tmp1
            elif tmp2:
                tmp.next = tmp2
            
            return dummy.next
        return sortFun(head, None)

# @lc code=end

