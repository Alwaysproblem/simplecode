#
# @lc app=leetcode.cn id=91 lang=python3
#
# [91] 解码方法
#

# @lc code=start
class Solution:
    def numDecodings(self, s: str) -> int:
        dp = [ 0 ] * (len(s) + 2)
        dp[0] = 1
        dp[1] = 1
        dp[2] = 1 if s[0] != "0" else 0

        for i in range(1, len(s)):
            if s[i] == '0':
                if s[i - 1] in ("1", "2"):
                    dp[i + 2] = dp[i + 2 - 2]
                else:
                    return 0
            elif s[i - 1] == '1':
                dp[i + 2] = dp[i + 2 - 1] + dp[i + 2 - 2]
            elif s[i - 1] == '2' and 1 <= int(s[i]) <= 6:
                dp[i + 2] = dp[i + 2 - 1] + dp[i + 2 - 2]
            else:
                dp[i + 2] = dp[i + 2 - 1]
        
        return dp[-1]
 # @lc code=end

if __name__ == "__main__":
    print(Solution().numDecodings("123"))
