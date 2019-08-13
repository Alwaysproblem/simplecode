#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/crush/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays

from itertools import accumulate

# Complete the arrayManipulation function below.
def arrayManipulation(n, queries):
    arr = [0] * n
    for a, b, k in queries:
        arr[a-1] += k
        if b < n:
            arr[b] -= k

    return max(accumulate(arr, lambda x,y: x+y))


if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    queries = []

    for _ in range(m):
        queries.append(list(map(int, input().rstrip().split())))

    result = arrayManipulation(n, queries)

    print(result)