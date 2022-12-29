#
# @lc app=leetcode.cn id=3 lang=python3
#
# [3] 无重复字符的最长子串
#

# @lc code=start
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        windows = []
        maxLen = 0
        n = len(s)
        i = 0
        while i < n:
            if s[i] not in windows:
                windows.append(s[i])
                maxLen = max(maxLen, len(windows))
                i += 1
            else:
                windows.pop(0)
        return maxLen

# @lc code=end

if __name__ == '__main__':
    print(Solution().lengthOfLongestSubstring("abcabcbb"))