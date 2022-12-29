#
# @lc app=leetcode.cn id=206 lang=python3
#
# [206] 反转链表
#

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# @lc code=start
# Definition for singly-linked list.
class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        if head is None:
            return head

        cur = head
        pre = None

        while cur.next is not None:
            n = cur.next
            cur.next = pre
            pre = cur
            cur = n
        cur.next = pre

        return cur
# @lc code=end

