#
# @lc app=leetcode.cn id=92 lang=python3
#
# [92] 反转链表 II
#
# from typing import List
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
# @lc code=start
# Definition for singly-linked list.
class Solution:
    def reverse(self, head:ListNode, tail:ListNode):
        if head is tail:
            return head

        cur = head
        pre = tail

        while cur.next is not tail:
            n = cur.next
            cur.next = pre
            pre = cur
            cur = n

        cur.next = pre

        return cur

    def reverseBetween(self, head: ListNode, left: int, right: int) -> ListNode:
        dummy = ListNode(-1)
        dummy.next = head
        l, r = dummy, dummy
        cur = dummy
        ind = 0
        while cur:
            if ind < left - 1:
                l = l.next
            if ind < right:
                r = r.next

            ind += 1
            cur = cur.next
    
        tmp = l.next
        nl = self.reverse(tmp, r.next)
        l.next = nl

        return dummy.next
        # return head
# @lc code=end

def printList(head: ListNode):
    cur = head
    while cur:
        if cur.next is not None:
            print(cur.val, "->", end=" ")
        else:
            print(cur.val, end="\n")
        cur = cur.next

if __name__ == '__main__':
    h = ListNode(1)
    # h = ListNode(3)
    # h.next = ListNode(5)
    cur = h
    for i in range(2, 6):
        cur.next = ListNode(i)
        cur = cur.next
    printList(h)
    # hh = Solution().reverse(h, )
    # hh = Solution().reverseBetween(h, 1, 2)
    hh = Solution().reverseBetween(h, 2, 4)
    printList(hh)