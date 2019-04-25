#!/bin/python3

import math
import os
import random
import re
import sys

from collections import Counter

# Complete the repeatedString function below.
def repeatedString(s, n):
    N = len(s)
    if N == 1 and s == 'a':
        return n
    else:
        occur = Counter(s)
        return n // N * occur['a'] + Counter(s[:n % N])['a']



if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    n = int(input())

    result = repeatedString(s, n)
    print(result)