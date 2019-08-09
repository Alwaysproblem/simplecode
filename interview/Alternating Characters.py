#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/alternating-characters/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=strings

from itertools import groupby
# Complete the alternatingCharacters function below.
def alternatingCharacters(s):
    return len(s) - len([*groupby(s)])


if __name__ == '__main__':
    q = int(input())

    for q_itr in range(q):
        s = input()

        result = alternatingCharacters(s)

        print(str(result))

#%%

#%%
