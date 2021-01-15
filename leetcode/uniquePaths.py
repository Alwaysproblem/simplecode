def uniquePaths(m: int, n: int) -> int:
    uP = [[1 for j in range(n)] for i in range(m)]

    for r in range(1, m):
        for c in range(1, n):                
            uP[r][c] = uP[r - 1][c] + uP[r][c - 1]

    return uP[m-1][n-1]

if __name__ == "__main__":
    uniquePaths(3, 2)