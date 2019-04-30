#!/bin/python3

import math
import os
import random
import re
import sys

def Merge(arr, l, m, r):
    cnt = 0
    s = []
    i, j = l, m + 1
    while i != m + 1 and j != r + 1:
        if arr[i] > arr[j]:
            s.append(arr[j])
            # suppose_ind = len(s) - 1
            cnt += m + 1 - l - (i - l) # the length of len - the current index because left > right, we need len(left) - i steps to put the right into the left.
            j += 1
        elif arr[i] <= arr[j]:
            s.append(arr[i])
            i += 1
    else:
        if i == m + 1:
            s += arr[j:r + 1]
        elif j == r + 1:
            s += arr[i: m + 1]
    arr[l: r+1] = s

    return cnt


# MergeSort(arr, l, len(arr) - 1, cnt)
def MergeSort(arr, l, r):
    if l > r:
        return 0
    elif r == l:
        return 0
    elif r - l == 1:
        if arr[r] < arr[l]:
            arr[r], arr[l] = arr[l], arr[r]
            return 1
        return 0
    else:
        m = (l + r) // 2
        cntl = MergeSort(arr, l, m)
        cntr = MergeSort(arr, m + 1, r)
        cntM = Merge(arr, l, m, r)
        return cntl + cntr + cntM

#wrong
# from collections import deque
# # Complete the countInversions function below.
# def countInversions(arr):
#     L = arr.copy()
#     L.sort()
#     if L == arr:
#         return 0
#     tmp = []
#     tab = {k:deque() for k in set(L)}
#     for ind, val in enumerate(L, 1):
#         tab[val].append(ind)
    
#     for i in arr:
#         tmp.append(tab[i].popleft())
    
#     res = sum([abs(ind - val) for ind, val in enumerate(tmp, 1)]) // 2

#     return res

# s = [2, 3, 1]
# cnt = MergeSort(s, 0, len(s) - 1)
# print(s)
# print(cnt)

def countInversions(arr):
    L = arr.copy()
    L.sort()
    if L == arr:
        return 0
    else:
        cnt = MergeSort(arr, 0, len(arr) - 1)
        return cnt

if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        n = int(input())

        arr = list(map(int, input().rstrip().split()))

        result = countInversions(arr)

        print(result)

