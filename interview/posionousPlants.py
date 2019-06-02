#!/bin/python3

import math
import os
import random
import re
import sys

#%%
"""this is the answer."""
from IPython.display import Image
Image("img/posion_plants_1.png")
#%%
Image("img/posion_plants_2.png")

#%%
# Complete the poisonousPlants function below.
def poisonousPlants(p):
    max_days = 0
    stack = []
    cur_date = 0
    for v in p:
        if len(stack) == 0:
            stack.append((v, 0))
        else:
            # posn, cur_date = stack.pop()
            if v > stack[-1][0]:
                stack.append((v, 1))
                max_days = max(max_days, 1)
            else:
                cur_date = stack[-1][1]
                while len(stack) != 0 and stack[-1][0] >= v:
                    _, cur_date_t = stack.pop()
                    if len(stack) == 0:
                        break
                    cur_date = max(cur_date, cur_date_t)

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
