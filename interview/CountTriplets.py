#!/bin/python3
#%%
import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/count-triplets-1/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps

from collections import Counter

def countTriplets(arr, r):
    # r2 = Counter()
    # r3 = Counter()
    r2 = {}
    r3 = {}
    count = 0
    
    for v in arr:
        if v in r3:
            try:
                count += r3[v]
            except KeyError:
                count = r3[v]
        
        if v in r2:
            try:
                r3[v*r] += r2[v]
            except KeyError:
                r3[v*r] = r2[v]
        try:
            r2[v*r] += 1
        except KeyError:
            r2[v*r] = 1

    return count

# def countTriplets(arr, r):
#     c = 0
#     for ind, v in enumerate(arr):
#         if v % r == 0:
#             lefti = Counter(arr[:ind])
#             righti = Counter(arr[ind + 1:])
#             c += lefti[v/r] * righti[v*r]
#     return c


if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nr = input().rstrip().split()

    n = int(nr[0])

    r = int(nr[1])

    arr = list(map(int, input().rstrip().split()))

    ans = countTriplets(arr, r)

    print(ans)
