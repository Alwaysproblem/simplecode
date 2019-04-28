#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the freqQuery function below.
from collections import Counter
# def freqQuery(queries):
#     a = Counter()
#     res = []
#     for mode, content in queries:
#         if mode == 1:
#             a[content] += 1
#         elif mode == 2:
#             if a[content] != 0:
#                 a[content] -= 1
#         elif mode == 3:
#             for i in a.keys():
#                 if a[i] == content:
#                     res.append(1)
#                     break
#             else:
#                 res.append(0)
#         else:
#             pass
#     return res

# from collections import Counter
def freqQuery(queries):
    # a = Counter()
    a = {}
    res = []
    for mode, content in queries:
        if mode == 1:
            try:
                a[content] += 1
            except KeyError:
                a[content] = 1
        elif mode == 2:
            if content in a.keys() and a[content] != 0:
                a[content] -= 1
        elif mode == 3:
            if content in set(a.values()):
                res.append(1)
            else:
                res.append(0)
        else:
            pass
    return res

if __name__ == '__main__':

    q = int(input().strip())

    queries = []

    for _ in range(q):
        queries.append(list(map(int, input().rstrip().split())))

    ans = freqQuery(queries)

    print('\n'.join(map(str, ans)))
