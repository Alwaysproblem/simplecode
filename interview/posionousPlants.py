#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the poisonousPlants function below.
def poisonousPlants(p):
    max_days = 0
    stack = [(p[0], 0)]

    for i, v in enumerate(p):
        if i != 0:
            if v > stack[-1][0]:
                stack.append((v, 1))
            else:
                cur_date = 0
                while len(stack) != 0 and stack[-1][0] >= v:
                    _, cur_date = stack.pop()
                    # max_days = max(max_days, cur_date)

                if len(stack) == 0:
                    stack.append((v, 0))
                else:
                    stack.append((v, cur_date + 1))
                    max_days = max(max_days, cur_date + 1)
    return max_days

if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    p = list(map(int, input().rstrip().split()))

    result = poisonousPlants(p)

    print(result)

    # fptr.write(str(result) + '\n')

    # fptr.close()
