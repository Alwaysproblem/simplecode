#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the whatFlavors function below.
def whatFlavors(cost, money):
    hashDic = {}
    for i, c in enumerate(cost, 1):
        if c in hashDic.keys():
            hashDic[c].append(i)
        else:
            hashDic[c] = [i]
    
    for ind, c in enumerate(cost, 1):
        if 2 * c == money and len(hashDic[c]) == 2:
                print(" ".join(map(str, hashDic[c])))
                return
        elif money - c in hashDic.keys():
            if len(hashDic[money - c]) == 1 and ind != hashDic[money - c][0]:
                print(ind, hashDic[money - c][0], sep=" ")
                return

if __name__ == '__main__':
    t = int(input())

    for t_itr in range(t):
        money = int(input())

        n = int(input())

        cost = list(map(int, input().rstrip().split()))

        whatFlavors(cost, money)