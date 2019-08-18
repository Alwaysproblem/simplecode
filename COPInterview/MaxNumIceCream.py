#!/bin/python3

import math
import os
import random
import re
import sys

import operator

#%%
# description
from IPython.display import Image, display

for f in ['img/MaxNumIceCream1.jpg', 'img/MaxNumIceCream2.jpg']:
    display(Image(filename=f))

#%%
# solution

from IPython.display import Image
Image('img/solution_maxIcecream.png')


#%%

def maxNumofIceCream(money, storage, cost):
    tmp = money + sum(map(operator.mul, storage, cost))
    return math.floor(tmp / sum(cost))

if __name__ == '__main__':
    n, m = list(map(int, input().split()))
    storage = list(map(int, input().split()))
    cost = list(map(int, input().split()))
    print(maxNumofIceCream(m, storage, cost))