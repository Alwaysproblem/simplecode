#
# @lc app=leetcode.cn id=2 lang=python3
#
# [2] 两数相加
#

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
# @lc code=start
class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        l1p = l1
        l2p = l2

        l3 = ListNode()
        l3p = l3
        last = l3
        flag = 0

        while l1p != None or l2p != None:
            if l1p is None:
                l3p.val += l2p.val
                if l3p.val >= 10:
                    flag = 1
                    l3p.val -= 10
                else:
                    flag = 0
                

            elif l2p is None:
                l3p.val += l1p.val
                if l3p.val >= 10:
                    flag = 1
                    l3p.val -= 10
                else:
                    flag = 0

            elif l2p.val + l1p.val + flag >= 10:
                l3p.val += l2p.val + l1p.val - 10
                flag = 1
            else:
                l3p.val += l2p.val + l1p.val
                flag = 0

            l1p = l1p.next if l1p != None else None
            l2p = l2p.next if l2p != None else None
            l3p.next = ListNode(val=flag)
            last = l3p
            l3p = l3p.next
        if last.next is not None and last.next.val == 0:
            last.next = None
        return l3
# @lc code=end

if __name__ == "__main__":
    s = Solution()
    s.addTwoNumbers([9,9,9,9,9,9,9], [9,9,9,9])