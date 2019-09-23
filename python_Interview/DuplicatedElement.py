import math
import os
import random
import re
import sys

import unittest

# first thought
def FindDuplication(W):
    if W == []:
        return -1
    HashT = {}
    for i in W:
        try:
            HashT[i] += 1
        except:
            HashT[i] = 1
    
    for i in HashT:
        if HashT[i] > 1:
            return i

    return -1

# Second thought
from operator import xor
from functools import reduce
def FindDuplication(W):
    if len(W) == 0:
        return -1
    a = reduce(xor, W) ^ reduce(xor, [k for k in set(W)])
    return a if a != 0 else -1


class Test(unittest.TestCase):
    def testFindDuplication(self):
        self.assertEqual(FindDuplication([1, 1, 2, 3, 4]), 1)
        self.assertEqual(FindDuplication([1, 1]), 1)
        self.assertEqual(FindDuplication([1, 2, 3, 4]), -1)
        self.assertEqual(FindDuplication([1, 3, 4, 2, 5, 3]), 3)
        self.assertEqual(FindDuplication([]), -1)

if __name__ == "__main__":
    unittest.main()
    # FindDuplication([1, 2, 3, 4])
