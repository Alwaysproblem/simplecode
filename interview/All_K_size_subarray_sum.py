#!/bin/python3

import math
import os
import random
import re
import sys


# accumulate can be used in the dynamic programming (1-D) f(n + 1) = f(n) + n

# #O(n^2)
# from itertools import accumulate
# import operator
# # Complete the maximumSum function below.
# def All_K_Size_SubarraySum(a, k = None):
#     if k == None:
#         k = len(a)
    
#     S = [0] * (k + 1)
#     for i, _ in enumerate(a, 1):
#         if i == 1:
#             S[i] = a[0]
#         elif i > 1:
#             b = a[:i]
#             # # first idea O(n)
#             # b.reverse()
#             # S[i] = S[i - 1] + sum(accumulate(b))

#             # second thought O(n)
#             weight = [i for i in range(1, k + 1)]
#             S[i] = S[i - 1] + sum(map(operator.mul, weight, b))

#     return S[-1]

# O(n)
def All_K_Size_SubarraySum(a, k = None):
    """
    arr[] = [1, 2, 3], n = 3
    All subarrays :  [1], [1, 2], [1, 2, 3], 
                    [2], [2, 3], [3]
    here first element 'arr[0]' appears 3 times    
        second element 'arr[1]' appears 4 times  
        third element 'arr[2]' appears 3 times

    Every element arr[i] appears in two types of subsets:
    i)  In subarrays beginning with arr[i]. There are 
        (n-i) such subsets. For example [2] appears
        in [2] and [2, 3].
    ii) In (n-i)*i subarrays where this element is not
        first element. For example [2] appears in 
        [1, 2] and [1, 2, 3].

    Total of above (i) and (ii) = (n-i) + (n-i)*i 
                                = (n-i)(i+1)
                                    
    For arr[] = {1, 2, 3}, sum of subarrays is:
    arr[0] * ( 0 + 1 ) * ( 3 - 0 ) + 
    arr[1] * ( 1 + 1 ) * ( 3 - 1 ) +
    arr[2] * ( 2 + 1 ) * ( 3 - 2 ) 

    = 1*3 + 2*4 + 3*3 
    = 20
    """
    if k == None:
        k = len(a)
    
    result = [0] * (k + 1)
  
    # computing sum of subarray  
    # using formula 
    for i in range(0, k):
        result[i + 1] = result[i] + (a[i] * (i+1) * (k-i))
    
    # return all subarray sum 
    return result[-1]


if __name__ == '__main__':

    a = list(map(int, input().rstrip().split()))

    result = All_K_Size_SubarraySum(a)

    print(result)
