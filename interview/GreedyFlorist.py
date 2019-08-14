#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the getMinimumCost function below.
def getMinimumCost(k, c):
    weight = [i // k + 1 for i in range(len(c))]
    c.sort(reverse=True)
    # res = sum([i*j for i,j in zip(weight, c)])
    res = sum(map(lambda z: z[0] * z[1], zip(weight, c)))
    return res

if __name__ == '__main__':
    nk = input().split()

    n = int(nk[0])

    k = int(nk[1])

    c = list(map(int, input().rstrip().split()))

    minimumCost = getMinimumCost(k, c)

    print(minimumCost)