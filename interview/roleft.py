#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/ctci-array-left-rotation/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays

# it can be applied with deque

# Complete the rotLeft function below.
def rotLeft(a, d):
    tmp = [0] * len(a)
    for ind, val in enumerate(a, 1):
        tmp[((ind - d) % len(a)) - 1] = val

    return tmp


if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nd = input().split()

    n = int(nd[0])

    d = int(nd[1])

    a = list(map(int, input().rstrip().split()))

    result = rotLeft(a, d)

    print(result)
