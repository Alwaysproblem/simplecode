import math
import os
import random
import re
import sys

# debug = True

def Solution(s, k):
    return "None"

def main():
    # input
    _, k = list(map(int, input().split()))
    Cards = input()

    # solution
    result = Solution(Cards, k)

    #print
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