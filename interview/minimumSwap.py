#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/minimum-swaps-2/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays

# Complete the minimumSwaps function below.
def minimumSwaps(arr):
    vis = {k:False for k in range(1, len(arr) + 1)}
    arrops = [(i, v) for i, v in enumerate(arr, 1)]
    arrops.sort(key = lambda x: x[1])
    ans = 0
    for i in range(1, n):
        ind, val = arrops[i - 1]
        if ind != val and vis[i] == False:
            j = i
            cycle_size = 0
            while not vis[j]:
                ind, val = arrops[j - 1]
                vis[val] = True
                j = ind
                cycle_size += 1
            ans += cycle_size - 1
    return ans

#my own code
# def minimumSwaps(arr):
#     b = arr.copy()
#     b.sort()
#     cnt = 0
#     s = []

#     g = dict(zip(b, arr))

#     unvisit = set(arr)

#     while len(unvisit) != 0:
#         t = unvisit.pop()
#         s = [t]
#         while len(s) != 0 and g[s[-1]] != s[0]:
#             unvisit.remove(g[s[-1]])
#             s.append(g[s[-1]])
#             cnt += 1
            
#     return cnt


if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    arr = list(map(int, input().rstrip().split()))

    res = minimumSwaps(arr)

    print(res)