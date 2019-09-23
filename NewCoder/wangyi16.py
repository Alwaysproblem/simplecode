import math
import os
import random
import re
import sys

#%%
import bisect

class cube(object):
    def __init__(self, ind, c):
        self.idx = ind
        self.h = c
    
    def __eq__(self, item):
        return (self.h == item.h) and (self.idx == item.idx)

    def __lt__(self, item):
        if self.h < item.h:
            return True
        elif self.h == item.h:
            if self.idx < item.idx:
                return True
        return False

    def __gt__(self, item):
        if self.h > item.h:
            return True
        elif self.h == item.h:
            if self.idx > item.idx:
                return True
        return False

    def __repr__(self):
        return f"({self.idx}, {self.h})"

a = [(2, 8), (1, 5), (3, 5)]
c = [cube(i, j) for i, j in a]
d = []
for cc in c:
    bisect.insort(d, cc)

print(d)


#%%


def Solution(s, k):
    pq = PriorityQueue(key= lambda x: if )
    return "None"

def main():
    # input
    n, k = list(map(int, input().split()))
    Cards = list(map(int, input().split()))

    # solution
    result = Solution(Cards, k)

    #print
    print(result)

if __name__ == "__main__":
    # if not debug:
    #     try:
    #         while True:
    #             main()
    #     except EOFError:
    #         exit()
    # else:
        main()