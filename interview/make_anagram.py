#!/bin/python3

import math
import os
import random
import re
import sys


# Complete the makeAnagram function below.
def makeAnagram(a, b):
    c, d = [0] * 26, [0] * 26

    for i in a:
        c[ord(i) - ord('a')] += 1

    for j in b:
        d[ord(j) - ord('a')] += 1
    
    cnt = 0
    for i,j in zip(c, d):
        if i != j:
            cnt += abs(i - j)

    return cnt

if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    a = input()

    b = input()

    res = makeAnagram(a, b)

    print(res)
