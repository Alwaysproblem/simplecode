from collections import Counter, defaultdict
from typing import List

def rotate(matrix):
    n = len(matrix)
    for i in range(n):
        for j in range(i, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
    for m in matrix:
        m.reverse()

if __name__ == "__main__":
    matrix = [
        [1,2,3],
        [4,5,6],
        [7,8,9]
    ]
    
    rotate(matrix)
    print(matrix[::-1])