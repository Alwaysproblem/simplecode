#!/bin/python3

import math
import os
import random
import re
import sys

#%%[marckdown]
# description:
# 小Q在假期的时候去探险，这个密室可以看成是 n*m 的小格子， 小Q最开始可以选择任意一个格子进入
# 此后的每一步 只能在  ,(x + 1, y - 1), (x + 1, y + 1), (x + 1, y) 中选择. 每个格子都有数字
# 当 Q 经过 为0 的格子后 分数取反， 求 能得最大分数 是多少

#%%
# dynamic programming.
from IPython.display import Image
Image('img/maxScoreSum.png')


#%%

def maxScore(g, n, m = 3):
    # res = [[0] * m for _ in range(n)]
    res_max = [[0] * m for _ in range(n)]
    res_min = [[0] * m for _ in range(n)]

    for i in range(m):
        # res[0][i] = g[0][i]
        res_max[0][i] = g[0][i]
        res_min[0][i] = g[0][i]
    
    for step in range(n - 1):
        for i in range(m):
            if g[step + 1][i] == 0:
                res_max[step + 1][i] = - min([res_min[step][j] for j in range(m)]) 
                # if we only have 3 choices, then we need to modify for j in range(m) to
                # for j in child(res_min[step][j])
                res_min[step + 1][i] = - max([res_max[step][j] for j in range(m)])
            else:
                res_max[step + 1][i] = max([res_max[step][j] + g[step + 1][i] for j in range(m)])
                res_min[step + 1][i] = min([res_min[step][j] + g[step + 1][i] for j in range(m)])

    return max(res_max[-1])

if __name__ == '__main__':
    n = int(input())

    Gmap = []
    for _ in range(n):
        q = list(map(int, input().split()))
        Gmap.append(q)

    print(maxScore(Gmap, n))


#%%
