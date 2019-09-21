#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/abbr/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming

# Complete the abbreviation function below.
def abbreviation(a:str, b:str):
    n, m = len(a) + 1, len(b) + 1
    res = [[False] * n for _ in range(m)]

    res[0][0] = True
    AA = a.upper()
    for i, ac in enumerate(AA, 1):
        if ac == b[0]:
            res[1][i] = True

    for i, ac in enumerate(a, 1):
        for j, bc in enumerate(b, 1):
            if res[j][i] == True:
                continue
            elif ac.islower():
                Cc = ac.upper()
                if Cc != bc:
                    res[j][i] = res[j][i - 1]
                else:
                    res[j][i] = any([res[j][i - 1], res[j - 1][i - 1]])
                pass
            else:
                if ac == bc:
                    res[j][i] = res[j - 1][i - 1]
    
    return "YES" if res[-1][-1] else "NO"


if __name__ == '__main__':

    q = int(input())

    for q_itr in range(q):
        a = input()

        b = input()

        result = abbreviation(a, b)

        print(result)
