import math
import os
import random
import re
import sys

# given an expression, search the positive integer roots.

#%%
def Solution(eq: str):
    dd = eq.split("=")
    a = '=='.join(dd)
    b = '<'.join(dd)
    c = '>'.join(dd)

    res = []

    Base = 1
    R  = 10 ** 7 + 1
    L = Base

    X = Base

    for _ in range(2):
        while L < R:
            if eval(a) == True:
                if X not in res:
                    res.append(X)
                elif X in res:
                    break
            elif eval(b) == True:
                L = X
                X = (L + R) // 2

            elif eval(c) == True:
                R = X
                X = (L + R) // 2

    return res[0] if len(res) ==  1 else -1


if __name__ == "__main__":
    eq = input()

    print(Solution(eq))