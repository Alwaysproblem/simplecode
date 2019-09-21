#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the candies function below.
def candies(n, arr):
    c = [1]
    d = 1
    for i, v in enumerate(arr):
        if i > 0:
            if v <= arr[i - 1]:
                d = 1
            else:
                d += 1
            c.append(d)
    
    print(c)
    return sum(c)

if __name__ == '__main__':

    n = int(input())

    arr = []

    for _ in range(n):
        arr_item = int(input())
        arr.append(arr_item)

    result = candies(n, arr)

    print(result)
