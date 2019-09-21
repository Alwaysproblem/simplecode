import math
import os
import random
import re
import sys

# 假设 m % x = x-1（x-1是能取到的最大余数，也就是说 m+1 是 x 的倍数）
# 如果 m+1 是所有数的倍数，则 f(m) 可以取到最大值，m+1 的值就是所有数的最小公倍数
n = int(input())
a = list(map(int, input().split(' ')))
print(sum(a) - n)

#%%
from functools import reduce

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def GCD(li):
    return reduce(gcd, li)

def lcm(a, b):
    return a*b // gcd(a, b)

def LCM(li):
    return reduce(lcm, li)

# LCM([1, 2, 3])
#%%
def calM(a, m):
    return sum(map(lambda x: m%x, a))

def optimalS(a):
    return calM(a, LCM(a) - 1)

def main():
    # input
    _ = input()
    a = list(map(int, input().split()))
    # Cards = input()

    # solution
    result = optimalS(a)

    #print
    print(result)

if __name__ == "__main__":
    main()