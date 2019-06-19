#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the pairs function below.
def pairs(k, arr):
    hashT = set(arr)
    resl = []
    for a_i in arr:
        if a_i - k in hashT:
            resl.append((a_i, a_i - k))

    return len(resl)

if __name__ == '__main__':
    nk = input().split()

    n = int(nk[0])

    k = int(nk[1])

    arr = list(map(int, input().rstrip().split()))

    result = pairs(k, arr)

    print(result)
