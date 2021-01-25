#
# @lc app=leetcode.cn id=50 lang=python3
#
# [50] Pow(x, n)
#

# @lc code=start
class Solution:
    def myPow(self, x: float, n: int) -> float:
        
        def Pow(X, N):
            if X == 0:
                return 0
            if N == 0:
                return 1.0
            else:
                y = Pow(X, N // 2)
                return y * y if N % 2 == 0 else y * y * X
        return Pow(x, n) if n >= 0 else 1.0 / Pow(x, -n)
# @lc code=end
if __name__ == "__main__":
    print(Solution().myPow(2, 5))
