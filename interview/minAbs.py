#!/bin/python3

import math
import os
import random
import re
import sys



# Complete the minimumAbsoluteDifference function below.
def minimumAbsoluteDifference(arr):
    def AbsSub(t):
        if len(t) == 2:
            return abs(t[0] - t[1])
        else:
            return 0
    arr.sort()
    diff = map(AbsSub, list(zip(arr, arr[1:])))
    
    return min(diff)


if __name__ == '__main__':

    n = int(input())

    arr = list(map(int, input().rstrip().split()))

    result = minimumAbsoluteDifference(arr)

    print(result)
