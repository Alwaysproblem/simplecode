#!/bin/python3

import os
import sys


#%%
class Queue(object):
    def __init__(self, data = None):
        if data == None:
            self.data = []
        else:
            self.data = data

    def Enqueue(self, item):
        self.data.append(item)

    def Dequeue(self):
        return self.data.pop(0)
    
    def qsize(self):
        return len(self.data)

    def isEmpty(self):
        return len(self.data) == 0

    def __repr__(self):
        return "Queue(" + ', '.join(map(str, self.data)) + ")"

    def __str__(self):
        return "Queue(" + ', '.join(map(str, self.data)) + ")"

    def __iter__(self):
        return self

    def __next__(self):
        if self.isEmpty():
            raise StopIteration
        else:
            return self.Dequeue()

    def __contains__(self, item):
        return item in self.data


class BTree():
    def __init__(self, val, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right

    def swapNodes(self):
        self.left, self.right = self.right, self.left

def show(subtree):
    if subtree.val == -1:
        return
    else:
        show(subtree.left)
        print(subtree.val, end = ' ')
        show(subtree.right)

def InputTree(indexes):
    # Nodes = enumerate(sum(indexes, [1]), 1)
    t = BTree(1)
    q = Queue()
    q.Enqueue(t)
    IDX = iter(indexes)

    while not q.isEmpty():
        cur = q.Dequeue()
        if cur.val == -1:
            continue
        l, r = next(IDX)

        cur.left = BTree(l)
        cur.right = BTree(r)

        q.Enqueue(cur.left)
        q.Enqueue(cur.right)

    return t

def Swap(tree: BTree , level: int, k: int):
    if tree.val == -1:
        return
    else:
        Swap(tree.left, level + 1, k)
        Swap(tree.right, level + 1, k)
        if level % k == 0:
            tree.swapNodes()

def swapNodes(indexes, queries):
    T = InputTree(indexes)
    # show(T)
    # print()
    for q in queries:
        Swap(T, 1, q)
        show(T)
        print()


# s = [[2, 3], [4, 5], [6, 7], [-1, -1], [-1, -1], [-1, -1], [-1, -1]]
# q = [2]

# swapNodes(s, q)

if __name__ == '__main__':
    n = int(input())

    indexes = []

    for _ in range(n):
        indexes.append(list(map(int, input().rstrip().split())))

    queries_count = int(input())

    queries = []

    for _ in range(queries_count):
        queries_item = int(input())
        queries.append(queries_item)

    swapNodes(indexes, queries)
