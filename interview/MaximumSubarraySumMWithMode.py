#!/bin/python3


import math
import os
import random
import re
import sys

# slideing windows can be treated as CycleMove and take top n number

# def CycleMove(lst, k):
#     return lst[k:] + lst[:k]

# https://www.hackerrank.com/challenges/maximum-subarray-sum/problem

import bisect
def maximumSumWithMode(a, m):
    mm,pr=0,0
    a1=[]
    for i in a:
        pr=(pr+i)%m
        mm=max(mm,pr)
        ind=bisect.bisect_left(a1,pr+1)
        if(ind<len(a1)):
            mm=max(mm,pr-a1[ind]+m)
        bisect.insort(a1,pr)
    return mm


# # O(n^2)
# # Complete the maximumSum function below.
# def maximumSum(a, m):
#     maxSum = 0
#     n = len(a)
#     for i in range(1, n + 1):
#         tmpSum = sum(a[:i])
#         if tmpSum % m >= maxSum:
#             maxSum = tmpSum % m
#         for j in range(0, n - i):
#             tmpSum = tmpSum - a[j] + a[j + i]
#             if tmpSum % m >= maxSum:
#                 maxSum = tmpSum % m
#     return maxSum


if __name__ == '__main__':
    q = int(input())

    for q_itr in range(q):
        nm = input().split()

        n = int(nm[0])

        m = int(nm[1])

        a = list(map(int, input().rstrip().split()))

        result = maximumSumWithMode(a, m)

        print(result)
