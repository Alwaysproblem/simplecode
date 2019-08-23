#!/bin/python3

import os
import sys


#
# Complete the swapNodes function below.





#

def TreeList(indexes):
    Nodes = sum(indexes, [1])
    NNode = len(Nodes)
    # NNode must be 2**k - 1
    tree = ["-"] * NNode
    m = (NNode + 1) // 2

    k = 1
    while 2 ** k - 1 <= NNode and m != 0:

        for i in range(1, 2 ** k):
            if tree[m * i - 1] == "-":
                item = Nodes.pop(0)
                tree[m * i - 1] = (k, item)
        k += 1
        m = (NNode + 1)// (2 ** k)

    return tree



s = [[2, 3], [4, 5], [6, 7], [-1, -1], [-1, -1], [-1, -1], [-1, -1]]

TreeList(s)

