import math
import os
import random
import re
import sys

debug = True

def swap(s):
    k = s.copy()
    for ind, v in enumerate(k):
        if v == s[0] and ind > 0:
            break
    
    k.pop(ind)
    k.pop(0)
    return k, ind - 1

def MinSwap(s):
    if len(s) % 2 != 0:
        return "Error"
    elif len(s) == 0:
        return 0
    elif s[1] == s[0]:
        return MinSwap(s[2:])
    else:
        k, times = swap(s)
        return times + MinSwap(k)

    return 

def main():
    # input
    n = int(input())
    a = list(map(int, input().split()))
    # Cards = input()

    # solution
    result = MinSwap(a)

    #print
    print(result)

if __name__ == "__main__":
    if not debug:
        try:
            while True:
                main()
        except EOFError:
            exit()
    else:
        main()