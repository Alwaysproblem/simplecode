#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/poisonous-plants/problem

#%%
"""this is the answer."""
from IPython.display import Image, display

for img in ["img/posion_plants_1.png", "img/posion_plants_2.png"]:
    display(Image(filename=img))

#%%
class Stack(object):
    def __init__(self, data = None):
        if data == None:
            self.data = []
        else:
            self.data = data
    
    def push(self, data):
        self.data.append(data)

    def pop(self):
        return self.data.pop()

    @property
    def top(self):
        return self.data[-1]

    def isEmpty(self):
        return len(self.data) == 0

    def __repr__(self):
        return "Stack(" + ','.join(map(str, self.data)) + ")"

# Complete the poisonousPlants function below.
def poisonousPlants(plants):
    s = Stack()
    mDay = 0

    for p in plants:
        if s.isEmpty():
            s.push((p, 0))
        elif s.top[0] < p:
            s.push((p, 1))
            mDay = max(mDay, 1)
        else:
            cur_day = s.top[1]
            while not s.isEmpty() and s.top[0] >= p:
                _, n_day = s.pop()
                cur_day = max(cur_day, n_day)
            else:
                if s.isEmpty():
                    s.push((p, 0))
                else:
                    s.push((p, cur_day + 1))
                    mDay = max(mDay, cur_day + 1)

    return mDay

if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    p = list(map(int, input().rstrip().split()))

    result = poisonousPlants(p)

    print(result)

    # fptr.write(str(result) + '\n')

    # fptr.close()
