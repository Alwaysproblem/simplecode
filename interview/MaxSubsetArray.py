#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the maxSubsetSum function below.
def maxSubsetSum(arr):
    res = [0] * (len(arr) + 1)

    for i, v  in enumerate(arr, 1):
        if i == 1:
            res[i] = v
        elif v > 0:
            res[i] = max(res[i - 2] + v, res[i - 1])
        else:
            res[i] = max(res[i - 2], res[i - 1])
        if res[i] < 0:
            res[i] = 0
    
    return res[-1]
    
if __name__ == '__main__':

    n = int(input())

    arr = list(map(int, input().rstrip().split()))

    res = maxSubsetSum(arr)

    print(res)
