import numpy as np

N = int(input())

l = []

for _ in range(N * 2):
    l.append([float(i) for i in input().split()])

T = np.array(l)

A = T[:N, :]
B = T[N:, :]

print(np.array(A@B, dtype=np.int))