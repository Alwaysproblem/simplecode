#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/ctci-ransom-note/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps

from collections import Counter

# Complete the checkMagazine function below.
def checkMagazine(magazine, note):
    cm = Counter(magazine)
    nm = Counter(note)
    for k in nm.keys():
        try:
            if cm[k] < nm[k]:
                raise ValueError
        except (KeyError, ValueError):
            print("No")
            return
    print("Yes")



if __name__ == '__main__':
    mn = input().split()

    m = int(mn[0])

    n = int(mn[1])

    magazine = input().rstrip().split()

    note = input().rstrip().split()

    checkMagazine(magazine, note)
