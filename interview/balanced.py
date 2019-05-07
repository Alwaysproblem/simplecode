#!/bin/python3

import math
import os
import random
import re
import sys


# https://www.hackerrank.com/challenges/balanced-brackets/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=stacks-queues

# Complete the isBalanced function below.
def isBalanced(s):
    stack = []
    opdic = {
        '}':'{',
        ']':'[',
        ')':'('
    }
    for i in s:
        if len(stack) != 0 and (i in opdic.keys()) and stack[-1] == opdic[i]:
            stack.pop()
        else:
            stack.append(i)
    
    return "YES" if len(stack) == 0 else "NO"


if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        s = input()

        result = isBalanced(s)

        print(result)
        # fptr.write(result + '\n')

    # fptr.close()
