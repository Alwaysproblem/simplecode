#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the hourglassSum function below.
def hourglassSum(arr):
    # conv_window = [[1] * 3, [0, 1, 0], [1] * 3]
    # print(conv_window)
    Row = len(arr)
    Col = len(arr[0])
    list_sum = []

    def conv(aa):
        return sum(aa[0] + [aa[1][1]] + aa[2])
    
    def chop(a, r, c):
        lista =[]
        for i in a[r: r + 3]:
            lista.append(i[c: c+3])
        # print(lista)
        return lista

    # r = conv(arr[0:3][0:3])
    # print(chop(arr, 1, 0))

    for row in range(0, Row - 2):
        for col in range(0, Col - 2):
            list_sum.append(conv(chop(arr, row, col)))

    return max(list_sum)

if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    arr = []

    for _ in range(6):
        arr.append(list(map(int, input().rstrip().split())))

    result = hourglassSum(arr)

    print(result)
