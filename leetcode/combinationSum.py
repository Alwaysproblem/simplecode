from typing import List
def combinationSum(candidates: List[int], target: int):
    if len(candidates) == 0:
        return []
    
    n = len(candidates) - 1
    com = []
    coms = []

    def backtrace(com):

        if sum(com) == target:
            coms.append(com.copy())
            return
        if sum(com) < target:
            for i in candidates:
                if len(com) == 0 or i >= com[-1]:
                    com.append(i)
                    backtrace(com)
                    com.pop()

    backtrace(com)

    return coms

print(combinationSum([2,3,5], 8))