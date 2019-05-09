#!/bin/python3

import math
import os
import random
import re
import sys

# find the longest commmon sequence.
# Complete the commonChild function below.
def commonChild(s1, s2):
    m, n = len(s1),len(s2)
    c = [[0 for _ in range(n + 1)] for _ in range(m + 1)]
    # result = []
    for i, c1 in enumerate(s1):
        for j, c2 in enumerate(s2):
            if c1 == c2:
                c[i+1][j+1] = c[i][j] + 1
            elif c[i][j + 1] > c[i + 1][j]:
                c[i+1][j+1] = c[i][j + 1]
            else:
                c[i+1][j+1] = c[i + 1][j]
            # else:
            #     c[i+1][j+1] = max(c[i][j+1], c[i +1][j])
    
    # for i in c:
    #     print(i)

    return c[-1][-1]


if __name__ == '__main__':

    s1 = input()

    s2 = input()

    result = commonChild(s1, s2)

    print(result)
    # fptr.write(str(result) + '\n')

    # fptr.close()