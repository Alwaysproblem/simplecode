from math import factorial
from math import ceil

def getPermutation(n: int, k: int):
    cans = [ str(i) for i in range(1, n + 1)]

    def backtrace(cans, n, k, com ):
        if len(cans) == 0:
            return ""
        if len(cans) == 1:
            return cans[0]
        div = com // n
        i = ceil(k / div) - 1 
        s = cans.pop(i)
        return s + backtrace(cans, n - 1, k - div * i, div)
    
    res = backtrace(cans, n, k, factorial(n))

    return res

getPermutation(4, 9)
