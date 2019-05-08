#!/bin/python3

import math
import os
import random
import re
import sys


# O(n^2)
# from collections import deque

# def window(seq, n=2):
#     it = iter(seq)
#     win = deque((next(it, None) for _ in range(n)), maxlen=n)
#     yield win
#     append = win.append
#     for e in it:
#         append(e)
#         yield win

# # Complete the riddle function below.
# def riddle(arr):

#     res = []
#     for i in range(1, len(arr) + 1):
#         lista = [min(j) for j in window(arr, i)]
#         res.append(max(lista))

#     return res

# O(n)
# see the minmaxriddle.png in the img folder.
def riddle(arr):
    n=len(arr)
    res=[0]*n
    S=[0]*n

    win=[0]
    for i in range(1,n):
        while len(win)>0 and arr[win[-1]]>=arr[i]:
            win.pop()
        if len(win)==0:
            S[i]=i+1-1
        else:
            S[i]=i-win[-1]-1
        win.append(i)

    win=[n-1]
    for i in range(n-2,-1,-1):
        while len(win)>0 and arr[i]<=arr[win[-1]]:
            win.pop()
        if len(win)==0:
            S[i]+=n-1-i
        else:
            S[i]+=win[-1]-i-1
        win.append(i)

    for i in range(n):
        if res[S[i]]<arr[i]:
            res[S[i]]=arr[i]

    for j in range(n-2,-1,-1):
        res[j]=max(res[j],res[j+1])

    return res


if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    arr = list(map(int, input().rstrip().split()))

    res = riddle(arr)

    print(" ".join(map(str, res)))
