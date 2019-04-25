import math
import os
import random
import re
import sys

# Complete the countingValleys function below.
def countingValleys(n, s):
    countV = 0
    level_h, level = 0, 0
    for c in s:
        if c == "U":
            level_h = level
            level += 1
        elif c == "D":
            level_h = level
            level -= 1
        else:
            pass
        if level_h < 0 and level == 0:
            countV += 1
    return countV

if __name__ == '__main__':
    n = int(input())

    s = input()

    result = countingValleys(n, s)
    print(result)


