class Node(object):
    def __init__(self, val = None, next_node = None):
        self.val = val
        self.next = next_node

    def print(self):
        p = self
        while p != None:
            if p.next is None:
                print(p.val)
            else:
                print(p.val, end="->")
            p = p.next


def reverse(head: Node) -> Node:
    cur = head
    pre = None

    while cur.next is not None:
        n = cur.next
        cur.next = pre
        pre = cur
        cur = n
    cur.next = pre

    return cur


if __name__ == '__main__':
    node = Node(0, next_node=Node(1, next_node=Node(2, next_node=Node(3, next_node=Node(4)))))
    node.print()
    reverse(node).print()
    # node.print()