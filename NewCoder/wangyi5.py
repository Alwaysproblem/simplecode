import math
import os
import random
import re
import sys

#%%
def splitShell(a, m):
    if m == 0:
        raise ValueError()
    Niushell = 0
    tmp = a
    while tmp > m:
        tmp = tmp - m - (tmp - m) // 10
        Niushell += m
    else:
        Niushell += tmp

    return Niushell
#%%
def minM(n):
    l = 1
    r = n
    while l < r:
        m = (l + r) // 2
        score = splitShell(n, m)
        if score >= n // 2:
            r = m
        else:
            l = m + 1
    else:
        if l == r:
            return l
        else:
            return m


def main():
    # input
    n = int(input())

    # solution
    result = minM(n)

    #print
    print(result)

if __name__ == "__main__":
    main()