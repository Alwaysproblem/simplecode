#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/triple-sum/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=search
# Complete the triplets function below.
from bisect import bisect_right
def triplets(A, B, C):

    A = sorted(set(A))
    B = sorted(set(B))
    C = sorted(set(C))

    res = 0
    for b in B:
        i = bisect_right(A, b)
        j = bisect_right(C, b)
        res += i * j
    return res


if __name__ == '__main__':

    lenaLenbLenc = input().split()

    lena = int(lenaLenbLenc[0])

    lenb = int(lenaLenbLenc[1])

    lenc = int(lenaLenbLenc[2])

    arra = list(map(int, input().rstrip().split()))

    arrb = list(map(int, input().rstrip().split()))

    arrc = list(map(int, input().rstrip().split()))

    ans = triplets(arra, arrb, arrc)

    print(ans)
