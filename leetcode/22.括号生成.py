#
# @lc app=leetcode.cn id=22 lang=python3
#
# [22] 括号生成
#
from typing import List
# @lc code=start
class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        if n == 0:
            return [""]
        
        l = 0
        r = 0

        com = list()
        coms = list()

        def backtrace(l, r, com):
            if len(com) == 2 * n:
                coms.append("".join(com))
                return
            
            if l < n :
                com.append("(")
                backtrace(l + 1, r, com)
                com.pop()
            
            if l > r:
                com.append(")")
                backtrace(l, r + 1, com)
                com.pop()

        backtrace(0, 0, com)

        return coms

# @lc code=end

if __name__ == "__main__":
    s = Solution()
    print(s.generateParenthesis(3))