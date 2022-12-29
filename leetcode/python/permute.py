def permute(arr):
    if len(arr) <= 1:
        return [arr]

    n = len(arr) - 1
    com = list()
    coms = list()

    def backtrace(com, cans):
        if len(cans) == 0:
        # if ind > n - 1:
            coms.append(com.copy())
            return
        
        cands = cans.copy()
        for c in cans:
            com.append(c)
            t = cands.pop(0)
            # cands.pop(ind)
            backtrace(com, cands)
            com.pop()
            cands.append(t)

    backtrace(com, arr)

    return coms

a = [1]

print(permute(a))

from itertools import permutations

print(len([*permutations(a)]) == len(permute(a)))