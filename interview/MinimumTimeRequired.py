#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the minTime function below.
# https://www.hackerrank.com/challenges/minimum-time-required/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=search
def totalProducts(numD, machines):
    return sum(map(lambda x: numD // x, machines))

def minTime(machines, goal):
    machines.sort()

    upper = goal // (len(machines) / machines[-1]) + 1
    lower = (goal // (len(machines) / machines[0]))

    while lower < upper:
        numD = (upper + lower) // 2
        total = totalProducts(numD, machines)
        if total < goal:
            lower = numD + 1
        else:
            upper = numD

    return int(lower)

if __name__ == '__main__':

    nGoal = input().split()

    n = int(nGoal[0])

    goal = int(nGoal[1])

    machines = list(map(int, input().rstrip().split()))

    ans = minTime(machines, goal)

    print(ans)
