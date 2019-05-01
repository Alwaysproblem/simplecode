#!/bin/python3
#%%
import math
import os
import random
import re
import sys

# Complete the activityNotifications function below.
# from statistics import median
from collections import Counter
#%%
def median(l, d):
    m = 0
    c = Counter(l)
    a = list(c.keys())
    a.sort()
    if d%2 == 0:
        find = d // 2
        for i, v in enumerate(a):
            if find - c[v] > 0:
                find = find - c[v]
            else:
                if c[v] == 1:
                    m = v + a[i + 1]
                else:
                    m = v * 2
                return m
    else:
        find = d // 2 + 1
        for i, v in enumerate(a):
            if find - c[v] > 0:
                find = find - c[v]
            else:
                m = v * 2
                return m

s = [3, 4, 2 ,3 ,6]
m = median(s, len(s))
print(m)

# #%%
# def activityNotifications(expenditure, d):
#     note = 0
#     for day in range(0, len(expenditure) - d):
#         ex_day = expenditure[day: d + day]
#         expend = expenditure[d + day]
#         med = median(ex_day, d)
#         if expend >= 2 * med:
#             note += 1
#     return note


# if __name__ == '__main__':
#     # fptr = open(os.environ['OUTPUT_PATH'], 'w')

#     nd = input().split()

#     n = int(nd[0])

#     d = int(nd[1])

#     expenditure = list(map(int, input().rstrip().split()))

#     result = activityNotifications(expenditure, d)

#     print(result)
#     # fptr.write(str(result) + '\n')

#     # fptr.close()
