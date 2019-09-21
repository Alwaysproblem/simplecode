import math
import os
import random
import re
import sys

debug = True

from collections import Counter
def Solution(a):
    cnt = Counter(a)
    ele = sorted(list(cnt))

    if len(ele) <= 1:
        return "Yes"
    if len(ele) > 3:
        return "No"
    elif len(ele) == 2:
        return "Yes"
        # if sum(ele) % 2 == 0:
        #     return "Yes"
        # else:
        #     return "No"
    elif len(ele) == 3:
        if ele[1]*2 == ele[0] + ele[-1]:
            return "Yes"
        else:
            return "No" 
    

def main():
    # input
    k = int(input())
    n = int(input())
    a = list(map(int, input().split()))

    # solution
    result = Solution(a)

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