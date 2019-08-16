#!/bin/python3

import math
import os
import random
import re
import sys

# https://www.hackerrank.com/challenges/new-year-chaos/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays


# O(n^2)
# # Complete the minimumBribes function below.
# def minimumBribes(q):
#     bribe = 0
    
#     for i, v in enumerate(q):
#         bri = len([j for j in q[i:] if j > v])
#         if bri > 2:
#             print("Too chaotic")
#         else:
#             bribe += bri

#     print(bribe)



#%%
# 1 2 3 4 5
# 2 1 5 3 4

# 0 1 2 3 4 -- index
# we count the number of one person brided.
# Anyone who bribed P cannot get to higher than one position in front of P's original position.


#%%

# O(n)
# # Complete the minimumBribes function below.
# def minimumBribes(q):
#     bribe = 0

#     for i, v in enumerate(q):
#         if v - i > 3:
#             print("Too chaotic")
#             return
#         else:
#             bribe += len([j for j in q[max(v-2, 0):i] if j >= v])
            
#     print(bribe)

# Complete the minimumBribes function below.
def minimumBribes(Q):
    #
    # initialize the number of moves
    moves = 0 
    #
    # decrease Q by 1 to make index-matching more intuitive
    # so that our values go from 0 to N-1, just like our
    # indices.  (Not necessary but makes it easier to
    # understand.)
    Q = [P-1 for P in Q]
    #
    # Loop through each person (P) in the queue (Q)
    for i,P in enumerate(Q):
        # i is the current position of P, while P is the
        # original position of P.
        #
        # First check if any P is more than two ahead of 
        # its original position
        if P - i > 2:
            print("Too chaotic")
            return
        #
        # From here on out, we don't care if P has moved
        # forwards, it is better to count how many times
        # P has RECEIVED a bribe, by looking at who is
        # ahead of P.  P's original position is the value
        # of P.
        # Anyone who bribed P cannot get to higher than
        # one position in front of P's original position.
        # if anyone who is larger than P is in front of P,
        # then P must be bribed at least once.
        # so we need to look from one position in front
        # of P's original position to one in front of P's
        # current position, and see how many of those 
        # positions in Q contain a number large than P.
        # In other words we will look from P-1 to i-1,
        # which in Python is range(P-1,i-1+1), or simply
        # range(P-1,i).  To make sure we don't try an
        # index less than zero, replace P-1 with
        # max(P-1,0)
        for j in range(max(P-1,0),i):
            if Q[j] > P:
                moves += 1
    print(moves)

if __name__ == '__main__':
    t = int(input())

    for t_itr in range(t):
        n = int(input())

        q = list(map(int, input().rstrip().split()))

        minimumBribes(q)
