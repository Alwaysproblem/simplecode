import math
import os
import random
import re
import sys

# give a number n, find all the combination of positive integer, the sum of which is n
# O(2^n)
def increaseOrder(newN, expression, res):
    if "+" in expression:
        k = [d >= str(newN) for d in expression.split("+")]
        if all(k) == True:
            res.append(f"{newN}+{expression}")
    else:
        if newN <= int(expression):
            res.append(f"{newN}+{expression}")

def getAllCombinationwithMemory(n, mem):
    if n < 0:
        return
    elif n == 1:
        mem[0] = ["1"]
        return ["1"]
    elif mem[n - 1] != None:
        return mem[n - 1]

    res = [f"{n}"]

    for i in range(1, n):
        Exp = getAllCombinationwithMemory(n - i, mem)

        for e in Exp:
            # if you want to ocnsider that "2+1+1" is different from "1+1+2" then uncomment these code.
            increaseOrder(i, e, res)
            # res.append(f"{i}+{e}")
    mem[n - 1] = res
    return res

def getAllCombination(n):
    if n < 0:
        return
    elif n == 1:
        return ["1"]

    res = [f"{n}"]

    for i in range(1, n):
        Exp = getAllCombination(n - i)

        for e in Exp:
            # if you want to ocnsider that "2+1+1" is different from "1+1+2" then uncomment these code.
            increaseOrder(i, e, res)
            # res.append(f"{i}+{e}")

    return res




if __name__ == "__main__":
    n = 25
    import time
    start = time.clock()
    res = getAllCombination(n)
    end = time.clock()
    print(f"without Memory: {-(start - end)}")

    start = time.clock()
    resm = getAllCombinationwithMemory(n, [None] * n)
    end = time.clock()
    print(f"with Memory: {-(start - end)}")
    assert(res == resm)
