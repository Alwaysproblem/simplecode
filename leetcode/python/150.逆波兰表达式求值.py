#
# @lc app=leetcode.cn id=150 lang=python3
#
# [150] 逆波兰表达式求值
#
from typing import *
# @lc code=start
from operator import add, sub, mul, truediv
class Solution:
    def evalRPN(self, tokens: List[str]) -> int:

        if not tokens:
            return 0
        cur = tokens.copy()
        op = {
            "+": add, 
            "-": sub, 
            "*": mul, 
            "/": truediv
        }

        sta = []

        while cur:
            
            if len(sta) == 0 or sta[-1] not in ("/", "*", "+", "-"):
                sta.append(cur.pop(0))
            
            elif sta[-1] in ("/", "*", "+", "-"):
                ops = sta.pop()
                num2 = int(sta.pop())
                num1 = int(sta.pop())
                ans = str(int(op[ops](num1, num2)))
                # if ops == "/" and num1 * num2 < 0 and num1 % num2 != 0:
                #     ans = str(op[ops](num1, num2) + 1)
                sta.append(ans)
        else:
            if len(sta) == 3:
                ops = sta.pop()
                num2 = int(sta.pop())
                num1 = int(sta.pop())
                sta.append(str(int(op[ops](num1, num2))))
            
            if len(sta) != 1:
                return 0
            else:
                ans = sta.pop()
                return int(ans)



# @lc code=end

if __name__ == "__main__":
    print(Solution().evalRPN(["0","3","/"]))