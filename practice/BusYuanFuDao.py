import math
import os
import random
import re
import sys

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


def BusOrder(n, m, N):
    F = []
    q = Queue()
    for i in N:
        q.Enqueue(i)
        if q.qsize() == m:
            F.append([j for j in q])
    else:
        if not q.isEmpty():
            F.append([j for j in q])
    
    F.reverse()
    return sum(F, [])

if __name__ == "__main__":
    n, m = list(map(int, input().split()))
    N = list(map(int, input().split()))

    result = BusOrder(n, m, N)

    print(' '.join(map(str, result)))