#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=strings

from collections import Counter
# Complete the isValid function below.
def isValid(s):
    hash_c = [0] * 26
    for i in s:
        hash_c[ord(i) - ord("a")] += 1
    ReC = Counter(hash_c)
    del(ReC[0])
    if len(ReC) > 2:
        return "NO"
    elif len(ReC) == 2:
        c_keys = list(ReC.keys())
        if 1 in c_keys and ReC[1] == 1:
            return "YES"
        elif 1 in ReC.values() and abs(c_keys[0] - c_keys[1]) == 1:
            return "YES"
        else:
            return "NO"
    else:
        return "YES"


if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = isValid(s)

    print(result)