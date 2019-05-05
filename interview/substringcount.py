#!/bin/python3
#%%
import math
import os
import random
import re
import sys

#O(n^3)
# def checksame(s):
#     return 1 if len(set(s)) == 1 else 0

# #%%
# def findallsubstring(s):
#     sub = []
#     for ind in range(len(s)):
#         for indc in range(ind, len(s)):
#             slice_str = s[ind: indc + 1]
#             sub.append(slice_str)
#     return sub

# #%%
# # Complete the substrCount function below.
# def substrCount(n, s):
#     sub = findallsubstring(s)
#     count = 0
#     for i in sub:
#         if len(i) == 1:
#             count += 1
#         elif len(i) % 2 == 0:
#             count += checksame(i)
#         elif len(i) % 2 != 0:
#             ss = i[:len(i)//2] + i[len(i)//2+1:]
#             count += checksame(ss)
#     return count

def triangular_number(n):
    return (n ** 2 + n - 2 * n)//2

# Complete the substrCount function below.
def substrCount(n, s):
    # every single letter should be counted
    count = len(s)

    #find the "xx.xx" 
    exp1 = r'(([a-z])\2*)(?!\1)(?=[a-z]\1)'
    m = re.finditer(exp1,s)
    count += sum([len(x.group(0)) for x in m])

    # find the "xxxx" and if "aaaa" then "a":4 "aa":3 "aaa":2 "aaaa":1. and "a" is already counted.
    # so we need to minus 4. the formular is n(n + 1) / 2 - n
    exp2 = r'([a-z])\1+'
    m = re.finditer(exp2,s)
    count += sum([triangular_number(len(x.group(0))) for x in m])

    return count


#%%
if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    s = input()

    result = substrCount(n, s)

    print(result)