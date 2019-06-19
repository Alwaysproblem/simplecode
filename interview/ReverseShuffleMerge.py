#!/bin/python3

import math
import os
import random
import re
import sys
#%%
#%%

# S = list(map(lambda x: ord(x)-97, input()))
# S = list(reversed(S))
# T = [0 for _ in range(26)]
# for x in S:
#   T[x]+=1
# R = list(map(lambda x: x//2, T))
# stack = []
# for x in S:
#   T[x]-=1
#   if not R[x]:
#     continue
#   while stack and stack[-1]>x and T[stack[-1]]>R[stack[-1]]:
#     R[stack[-1]]+=1
#     stack.pop()
#   if R[x]:
#     stack.append(x)
#     R[x]-=1
# stack = list(map(lambda x: chr(x+97), stack))
# print(''.join(stack))


from collections import Counter
def reverseShuffleMerge(s):
    s = list(s)
    s.reverse()
    Cnt = Counter(s)
    assume = Counter(s)
    for c in Cnt.keys():
        Cnt[c] //= 2
    stack = []
    for c in s:
        assume[c] -= 1
        if Cnt[c] == 0:
            continue
        while stack and stack[-1] > c and assume[stack[-1]] > Cnt[stack[-1]]:
            a = stack.pop()
            Cnt[a] += 1
        if Cnt[c] != 0:
            stack.append(c)
            Cnt[c] -= 1

    return ''.join(stack)

if __name__ == '__main__':
    s = input()
    result = reverseShuffleMerge(s)
    print(result)

