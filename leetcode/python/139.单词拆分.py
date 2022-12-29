#
# @lc app=leetcode.cn id=139 lang=python3
#
# [139] 单词拆分
#
from typing import *
# @lc code=start
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        dp = [False] * (len(s) + 1)
        dp[0] = True

        for i in range(1, len(s) + 1):
            for word in wordDict:
                if len(word) <= i and dp[i - len(word)]:
                    if s[i - len(word):i] == word:
                        dp[i] = True
        
        return dp[len(s)]



# @lc code=end

