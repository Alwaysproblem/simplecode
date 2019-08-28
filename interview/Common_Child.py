#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/common-child/problem

def printarr(s):
    m, n = len(s), len(s[0])
    for i in range(m):
        for j in range(n):
            print(s[i][j], end = '    ')
        print()

def commonChild(s1, s2, show = False):
    m, n = len(s1), len(s2)
    c = [[0 for i in range(n + 1)] for j in range(m + 1)]
    d = [['0' for i in range(n + 1)] for j in range(m + 1)]
    setl = []

    for i, c1 in enumerate(s1, 1):
        for j, c2 in enumerate(s2, 1):
            if c1 == c2:
                c[i][j] = c[i - 1][j - 1] + 1
                d[i][j] = "↖"
            else:
                c[i][j] = max(c[i - 1][j], c[i][j - 1])
                if c[i - 1][j] >= c[i][j - 1]:
                    d[i][j] = "↑"
                else:
                    d[i][j] = "←"

    if show == True:
        printarr(c)
        print()
        printarr(d)
        print(''.join(setl))
        a = m
        b = n
        while a > 0 and b > 0:
            if d[a][b] == "↖":
                setl.append(s1[a-1])
                a -= 1
                b -= 1
            elif d[a][b] == "↑":
                a -= 1
            else:
                b -= 1
        setl.reverse()
        print(''.join(setl))
        return ''.join(setl)

    return c[-1][-1]

if __name__ == '__main__':

    s1 = input()

    s2 = input()

    result = commonChild(s1, s2, True)

    print(result)
    # fptr.write(str(result) + '\n')

    # fptr.close()

#%%
# c = [[None for i in range(3)] for j in range(4)]

#%%
