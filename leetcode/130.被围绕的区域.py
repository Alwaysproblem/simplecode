#
# @lc app=leetcode.cn id=130 lang=python3
#
# [130] 被围绕的区域
#
from typing import *
# @lc code=start
class Solution:
    def solve(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """

        if len(board) <= 2 or len(board[0]) <= 2:
            return

        row = len(board)
        col = len(board[0])

        def dfs(i, j):
            if i < 0 or i>=row or j < 0 or j >= col or board[i][j] != "O":
                return

            board[i][j] = "A"

            dfs(i - 1, j)
            dfs(i + 1, j)
            dfs(i, j - 1)
            dfs(i, j + 1)
        
        for i in range(row):
            dfs(i, 0)
            dfs(i, col - 1)
        
        for j in range(col):
            dfs(0, j)
            dfs(row - 1, j)
        
        for i in range(row):

            for j in range(col):
                if board[i][j] == "O":
                    board[i][j] = "X"
                elif board[i][j] == "A":
                    board[i][j] = "O"

# @lc code=end

if __name__ == '__main__':
    board = [['X', 'X', 'X', 'X'], 
             ['X', 'O', 'O', 'X'], 
             ['X', 'X', 'O', 'X'], 
             ['X', 'O', 'X', 'X']]
    Solution().solve(board)
    print(board)