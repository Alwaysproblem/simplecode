
res = []
def generateParenthesis(n: int):
    
    def backtrack(l, r, S):
        if len(S) == 2 * n:
            res.append("".join(S))
            return
        if l < n:
            S.append("(")
            backtrack(l + 1, r, S)
            S.pop()
        if r < l:
            S.append(")")
            backtrack(l, r + 1, S)
            S.pop()

    backtrack(0,0,[])

generateParenthesis(2, res)
print(res)
