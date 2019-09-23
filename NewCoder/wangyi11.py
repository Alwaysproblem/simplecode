import math
import os
import random
import re
import sys

def Score(c, n):
    sc = 0
    S = [[] for _ in range(n)]
    for i in c:
        S[i - 1].append(i)
        if len([0 for s in S if len(s) != 0]) == n:
            sc += 1
            for s in S:
                s.pop(0)

    return sc

def main():
    # input
    n, m = list(map(int, input().split()))
    c = list(map(int, input().split()))

    # solution
    result = Score(c, n)

    #print
    print(result)

if __name__ == "__main__":
    main()