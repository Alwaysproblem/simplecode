#!/bin/python3

import math
import os
import random
import re
import sys

# def subarraySum(a):
#     import bisect
#     mm,pr=0,0
#     a1=[]
#     for i in a:
#         pr=(pr+i)%m
#         mm=max(mm,pr)
#         ind=bisect.bisect_left(a1,pr+1)
#         if(ind<len(a1)):
#             mm=max(mm,pr-a1[ind]+m)
#         bisect.insort(a1,pr)
#     return mm

def subarraySum(a):
    import bisect
    mm,pr=0,0
    a1=[]
    for i in a:
        pr = pr+i
        mm = mm + pr
        ind=bisect.bisect_left(a1,pr+1)
        if ind < len(a1):
            mm = mm + pr-a1[ind] + pr + 1
        bisect.insort(a1, pr)
    return mm

# # O(n^2)
#     Sum = 0
#     n = len(a)
#     for i in range(1, n + 1):
#         tmpSum = sum(a[:i])
#         Sum += tmpSum
#         for j in range(0, n - i):
#             tmpSum = tmpSum - a[j] + a[j + i]
#             Sum += tmpSum
#     return Sum

if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    arr_count = int(input().strip())

    arr = []

    for _ in range(arr_count):
        arr_item = int(input().strip())
        arr.append(arr_item)

    result = subarraySum(arr)

    print(result)

    # fptr.write(str(result) + '\n')

    # fptr.close()
