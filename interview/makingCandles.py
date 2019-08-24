#!/bin/python3

import math
import os
import random
import re
import sys


def minimumPasses(machine, worker, p, n): 
    if n <= p: 
        return math.ceil(n / (machine * worker))
    curr = candy = 0 
    ans = float('inf')
    while candy < n:
        if candy < p:
            i = math.ceil((p - candy) / (machine * worker))
            curr += i
            candy += machine * worker * i
            continue
        buy,candy = divmod(candy , p) 
        total = machine + worker + buy 
        half = total // 2
        if machine > worker : 
            machine = max(machine, half) 
            worker = total - machine
        else:
            worker = max(worker, half) 
            machine = total - worker
        curr += 1 
        candy += machine * worker 
        ans = min(ans, curr + math.ceil((n - candy) / (machine * worker)))
       
    return min(ans, curr)


if __name__ == '__main__':

    mwpn = input().split()

    m = int(mwpn[0])

    w = int(mwpn[1])

    p = int(mwpn[2])

    n = int(mwpn[3])

    result = minimumPasses(m, w, p, n)

    print(result)
