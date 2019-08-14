#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/luck-balance/problem
# Complete the luckBalance function below.
def luckBalance(k, contests):
    L = [i for i, _ in contests]
    T = [j for _, j in contests]

    if k >= len([i for i in T if i != 0]):
        return sum(L)
    else:
        imp = [L[j] for j in range(len(L)) if T[j] != 0]
        imp.sort()
        return sum(L) - 2 * sum(imp[0:len(imp) - k])


if __name__ == '__main__':
    nk = input().split()

    n = int(nk[0])

    k = int(nk[1])

    contests = []

    for _ in range(n):
        contests.append(list(map(int, input().rstrip().split())))

    result = luckBalance(k, contests)

    print(result)
