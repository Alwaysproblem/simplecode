#
# @lc app=leetcode.cn id=5 lang=python3
#
# [5] 最长回文子串
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        if n == 0:
            return ""
        
        res = s[0]
        def extend(i, j, s):
            while (i>=0 and j < len(s) and s[i] == s[j]):
                i -= 1
                j += 1
            return s[i+1: j]
        
        for i in range(len(s)):
            e1 = extend(i, i, s)
            e2 = extend(i, i+1, s)
            if max([len(e1), len(e2)]) > len(res):
                res = e1 if len(e1) > len(e2) else e2
        return res
# @lc code=end

