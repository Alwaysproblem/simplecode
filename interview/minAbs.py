#!/bin/python3

import math
import os
import random
import re
import sys



# Complete the minimumAbsoluteDifference function below.
def minimumAbsoluteDifference(arr):
    arr.sort()
    diff = map(lambda x: abs(x[1] - x[0]), zip(arr, arr[1:]))
    return min(diff)


if __name__ == '__main__':

    n = int(input())

    arr = list(map(int, input().rstrip().split()))

    result = minimumAbsoluteDifference(arr)

    print(result)
