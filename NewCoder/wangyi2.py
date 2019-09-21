import math
import os
import random
import re
import sys

from collections import Counter
def ChooseCard(s, k):
    cnt = Counter(s)
    priority = [(char, cnt[char]) for char in cnt]
    priority.sort(key= lambda x: x[1], reverse = True)

    chosen = k
    score = 0
    while chosen > 0:
        _, t = priority.pop(0)
        if t > chosen:
            score += chosen * chosen
            break
        score += t * t
        chosen -= t

    return score


if __name__ == "__main__":
    try:
        while True:
            n, k = list(map(int, input().split()))
            Cards = input()

            print(ChooseCard(Cards, k))
    except EOFError:
        exit()