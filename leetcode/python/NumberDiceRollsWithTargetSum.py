import math
import os
import random
import re
import sys

def numRollsToTarget(d: int, f: int, target: int):
    '''

    >>> d = 1; f = 6;target = 3
    >>> numRollsToTarget(d, f, target)
    1
    >>> d = 2; f = 6;target = 7
    >>> numRollsToTarget(d, f, target)
    6
    >>> d = 2; f = 5;target = 10
    >>> numRollsToTarget(d, f, target)
    1
    >>> d = 1; f = 2;target = 3
    >>> numRollsToTarget(d, f, target)
    0
    >>> d = 30; f = 30;target = 500
    >>> numRollsToTarget(d, f, target)
    222616187
    '''
    # if d * f < target:
    #     return 0
    # elif target <= 0:
    #     return 0
    # elif d == 1 and f >= target:
    #     return 1
    # else:
    #     cnt = 0
    #     # res = [[0] * (d + 1) for _ in range(f + 1)]
    #     for k in range(1, f + 1):
    #         a = numRollsToTarget(d - 1, f, target - k)
    #         b = numRollsToTarget(d - 1, f, k)
    #         cnt += a*b
    if d * f < target:
        return 0
    elif target <= 0:
        return 0
    elif d == 1 and f >= target:
        return 1
    else:
        res = [[0] * (target + 1) for i in range(d + 1)]

        dd = min(target, f)
        for face in range(1, dd+1):
            res[1][face] = 1
        
        for D in range(2, d + 1):
            for t in range(1, target + 1):
                for k in range(1, min(f+1, t)):
                    res[D][t] += res[D - 1][t - k]

        cnt = res[D][target]

    return cnt % (10**9 + 7)


if __name__ == "__main__":
    import doctest
    doctest.testmod()
    # d = 30
    # f = 30
    # target = 500
    # print(numRollsToTarget(d, f, target))
    # a1 = list(map(int, input().split()))
    # a2 = list(map(int, input().split()))
    # a1 = [2,3,1,3,2,4,6,7,9,2,19]
    # a2 = [2,1,4,3,9,6]

    # print(numRollsToTarget(a1, a2))