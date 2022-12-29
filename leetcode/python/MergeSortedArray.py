#%%
from collections import deque
from statistics import median

def MergeSortedArray(nums1: list, nums2: list) -> float:
    n1 = deque(nums1)
    n2 = deque(nums2)
    result = []

    while not len(n1) == 0 and not len(n2) == 0:
        t1 = n1.popleft()
        t2 = n2.popleft()

        if t1 > t2:
            result.append(t2)
            n1.appendleft(t1)
        elif t1 < t2:
            result.append(t1)
            n2.appendleft(t2)
        else:
            result.append(t1)
            result.append(t2)
    else:
        while not len(n1) == 0:
            result.append(n1.popleft())
        
        while not len(n2) == 0:
            result.append(n2.popleft())
    
    return result




if __name__ == "__main__":
    a = [1,3,5]
    b = [2,4,6]

    print(MergeSortedArray(a, b))


#%%
