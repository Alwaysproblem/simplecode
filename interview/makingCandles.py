#!/bin/python3

import math
import os
import random
import re
import sys

def maxNcandies(m, w, p, total):
    c = math.floor(total/ p)
    axes = (w + c - m) / 2

    if axes <= 0:
        a = 0
    elif axes >= c :
        a = c
    else:
        a = round(axes)
    
    b = c - a

    rest = total - p*c
    return a, b, rest


# Complete the minimumPasses function below.
def minimumPasses(m, w, p, n):
    rest = 0
    day = 0
    Total = 0
    ans = math.inf
    while  Total < n:
        Total = m * w + rest
        day += 1
        ans = min(ans, day + math.ceil((n - Total) / (m * w)))
        a, b, rest = maxNcandies(m, w, p, Total)
        m += a
        w += b

    return min(ans, day)


# def minimumPasses(machine, worker, p, n): 
#     if n <= p: 
#         return math.ceil(n / (machine * worker))
#     curr = candy = 0 
#     ans = float('inf')
#     while candy < n:
#         if candy < p:
#             i = math.ceil((p - candy) / (machine * worker))
#             curr += i
#             candy += machine * worker * i
#             continue
#         buy,candy = divmod(candy , p) 
#         total = machine + worker + buy 
#         half = total // 2
#         if machine > worker : 
#             machine = max(machine, half) 
#             worker = total - machine
#         else:
#             worker = max(worker, half) 
#             machine = total - worker
#         curr += 1 
#         candy += machine * worker 
#         ans = min(ans, curr + math.ceil((n - candy) / (machine * worker)))
       
#     return min(ans, curr)



if __name__ == '__main__':

    mwpn = input().split()

    m = int(mwpn[0])

    w = int(mwpn[1])

    p = int(mwpn[2])

    n = int(mwpn[3])

    result = minimumPasses(m, w, p, n)

    print(result)
