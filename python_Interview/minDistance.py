import math
import os
import random
import re
import sys

# find the minimum index distance between number 1 and number 2.
def minDistance(arr, num1, num2):
    if arr == None or len(arr) <= 0:
        print("there is something wrong with input parameter.")
        return math.inf
    lastpos1 = -1
    lastpos2 = -1
    minDis = math.inf

    for i, a in enumerate(arr):
        if a == num1:
            lastpos1 = i
            if lastpos2 >= 0:
                minDis = min(minDis, lastpos1 - lastpos2)
            
        if a == num2:
            lastpos2 = i
            if lastpos1 >= 0:
                minDis = min(minDis, lastpos2 - lastpos1)

    return minDis


if __name__ == "__main__":
    res = minDistance([4, 5, 6, 4, 7, 4, 6, 4, 7, 8, 5, 6, 4, 3, 10, 8], 4, 8)
    print(res)
