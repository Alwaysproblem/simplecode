#!/bin/python3

import math
import os
import random
import re
import sys
#%%
#%%

# https://www.hackerrank.com/challenges/reverse-shuffle-merge/problem


class Stack(object):
    def __init__(self, data = None):
        if data == None:
            self.data = []
        else:
            self.data = data
    
    def push(self, data):
        self.data.append(data)

    def pop(self):
        return self.data.pop()

    @property
    def top(self):
        return self.data[-1]

    def isEmpty(self):
        return len(self.data) == 0

    def __repr__(self):
        return "Stack(" + ','.join(map(str, self.data)) + ")"

from collections import Counter
# Complete the reverseShuffleMerge function below.
def reverseShuffleMerge(s):
    Cnt_A = {}
    Cnt_S = Counter(s)
    S_list = list(s)
    ss = Stack()
    assume = Cnt_S.copy()

    for i in Counter(s):
        Cnt_A[i] = Cnt_S[i] // 2
    
    S_list.reverse()
    for c in S_list:
        assume[c] -= 1
        if Cnt_A[c] == 0:
            continue
        
        while not ss.isEmpty() and ss.top > c and assume[ss.top] > Cnt_A[ss.top]:
            a = ss.pop()
            Cnt_A[a] += 1
        
        if Cnt_A[c] != 0:
            ss.push(c)
            Cnt_A[c] -= 1

    return ''.join(ss.data)

if __name__ == '__main__':
    s = input()
    result = reverseShuffleMerge(s)
    print(result)

