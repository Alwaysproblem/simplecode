import math
import os
import random
import re
import sys

# debug = True
from itertools import accumulate
def SearchX(N, m):
    NN = list(accumulate(N, lambda x, y: x + y))
    l = 0
    r = len(N) - 1

    while l < r:
        mid = (l + r) // 2
        if NN[mid] > m:
            r = mid 
        elif NN[mid] < m:
            l = mid + 1
        else:
            return mid + 1
    else:
        if l == r:
            return l + 1

def main():
    # input
    n = int(input())
    N= list(map(int, input().split()))
    m = int(input())
    M= list(map(int, input().split()))

    # solution
    for mm in M:
        result = SearchX(N, mm)
        print(result)

if __name__ == "__main__":
    # if not debug:
    #     try:
    #         while True:
    #             main()
    #     except EOFError:
    #         exit()
    # else:
        main()