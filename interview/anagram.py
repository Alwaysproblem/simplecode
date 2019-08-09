#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the anagram function below.
# hanming distance
from collections import Counter
def anagram(s):
    if len(s) % 2 == 0:
        return sum((Counter(s[0:len(s)//2]) - Counter(s[len(s)//2:])).values())
    else:
        return "-1"


if __name__ == '__main__':

    q = int(input())

    for q_itr in range(q):
        s = input()

        result = anagram(s)

        print(result)