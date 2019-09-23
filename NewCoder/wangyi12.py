import math
import os
import random
import re
import sys

#%%
# O(n)
# window slider generator
def WindowSlider(seq, n=2):
    it = iter(seq)
    win = list((next(it, None) for _ in range(n)))
    mm = sum(win)
    # yield mm
    for e in it:
        tmp = win.pop(0)
        win.append(e)
        if mm - tmp + e > mm:
            mm = mm - tmp + e
        # yield mm
    return mm

# def largestkSum(I, k):
#     return max([w for w in WindowSlider(I, k)])

WindowSlider([1, 2, 3, 4])

#%%
def MaxInterest(I, awake, k):
    sc = 0
    for ind, a in enumerate(awake):
        if a == 1:
            sc += I[ind]
            I[ind] = 0

    return sc + WindowSlider(I, k)

def main():
    # input
    _, k = list(map(int, input().split()))
    I = list(map(int, input().split()))
    awake = list(map(int, input().split()))

    # solution
    result = MaxInterest(I, awake, k)

    #print
    print(result)

if __name__ == "__main__":
    main()