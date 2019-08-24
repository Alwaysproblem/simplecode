#!/bin/python3

import math
import os
import random
import re
import sys

import math
def maxNcandies(m, w, p, total):
    c = math.floor((m * w  + total)/ p)
    axes = (w + c - m) / 2

    if axes <= 0:
        a = 0
    elif axes >= c :
        a = c
    else:
        a = round(axes)
    
    b = c - a

    rest = m*w + total - p*c
    return a, b, rest


# Complete the minimumPasses function below.
def minimumPasses(m, w, p, n):
    if m * w >= n:
        return 1
    rest = 0
    day = 1
    while True:
        a, b, rest = maxNcandies(m, w, p, rest)
        m += a
        w += b
        if m * w + rest >= n:
            return day
        day += 1
    
    return day

if __name__ == '__main__':

    mwpn = input().split()

    m = int(mwpn[0])

    w = int(mwpn[1])

    p = int(mwpn[2])

    n = int(mwpn[3])

    result = minimumPasses(m, w, p, n)

    print(result)
