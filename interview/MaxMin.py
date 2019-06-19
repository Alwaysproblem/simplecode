#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the maxMin function below.
def maxMin(k, arr):
    arr.sort()
    M = math.inf
    for i in range(len(arr) - k + 1):
        if arr[i+k-1] - arr[i] < M:
            M = arr[i+k-1] - arr[i]

    return M

if __name__ == '__main__':
    n = int(input())

    k = int(input())

    arr = []

    for _ in range(n):
        arr_item = int(input())
        arr.append(arr_item)

    result = maxMin(k, arr)

    print(result)