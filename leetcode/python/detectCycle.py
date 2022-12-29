# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


def detectCycle(head: ListNode) -> ListNode:
    visited = {}
    p = head
    index = 0
    while p.next is not None:
        if p not in visited:
            visited[p] = index
        else:
            return visited[p]
        p = p.next
        index += 1

print(detectCycle())