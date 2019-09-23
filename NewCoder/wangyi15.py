import math
import os
import random
import re
import sys

def Solution(k):
    a, b, c = k

    X = max(max(a * b, a + b) * c, max(a * b, a + b) + c)
    Y = max(max(b * c, b + c) * a, max(b * c, b + c) + a)

    return max(X, Y)


def main():
    # input
    k = list(map(int, input().split()))

    # solution
    result = Solution(k)

    #print
    print(result)

if __name__ == "__main__":
    main()