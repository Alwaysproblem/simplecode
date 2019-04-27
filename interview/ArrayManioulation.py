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
    lista = [0] * n
    for a, b, k in queries:
        lista[a - 1] += k
        if b < len(lista):
            lista[b] -= k
    res = accumulate(lista, lambda x, y: x + y)
    return max(res)


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