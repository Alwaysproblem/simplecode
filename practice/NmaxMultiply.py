

#%%[markdown]
# $A = \{a_i\}_{1}^{N}$
# ### let $f(k)$ is the best selection of k number that maximize the products.
# ### we considered the $f(k+2)$:
# ### $f(k + 2) = max\{f(k) \times max(b{i} \times b_{i+1}), f(k) \times min(b{i} \times b_{i+1})\}$
# ### where the $b_i$ is selected from $A$ \ $\{b_j\}_1^k$.

#%%
from functools import reduce

n = int(input())
a = list(map(int, input().split()))

def Top2Number(b, mode):
    b = b.copy()
    if mode == 'max':
        if all([i < 0 for i in b]):
            top1 = min(b)
            b.remove(top1)
            top2 = min(b)
        else:
            top1 = max(b)
            b.remove(top1)
            top2 = max(b)
    elif mode == 'min':
        if all([i < 0 for i in b]):
            top1 = max(b)
            b.remove(top1)
            top2 = max(b)
        else:
            top1 = min(b)
            b.remove(top1)
            top2 = min(b)

    return top1, top2


def FindTwoProducts(a: list, mode = 'max')-> tuple:
    maxProd, twoNum = 0, ()
    # two number are both pos

    pos = [i for i in a if i > 0]
    # two number are both neg
    neg = [i for i in a if i < 0]

    if len(pos) < 2:
        top1, top2 = Top2Number(neg, mode)
        maxProd = top1 * top2
        twoNum = (top1, top2)
    elif len(neg) < 2:
        top1, top2 = Top2Number(pos, mode)
        maxProd = top1 * top2
        twoNum = (top1, top2)
    else:
        Ptop1, Ptop2 = Top2Number(pos, mode)
        Ntop1, Ntop2 = Top2Number(neg, mode)
        if mode == 'max':
            maxProd = max([Ptop1 * Ptop2, Ntop1 * Ntop2])
        elif mode == 'min':
            maxProd = min([Ptop1 * Ntop2, Ntop1 * Ptop2])
        
        if maxProd == Ptop1 * Ptop2:
            twoNum = (Ptop1, Ptop2)
        else:
            twoNum = (Ntop1, Ntop2)

    return maxProd, twoNum


def NmaxMultiply(a, n = 3, debug = False):
    res = [0] * (n + 1)
    rest_elem = [0] # occupy position to convert index starting with 1
    del_elem = [0]

    for i in range(1, n + 1):
        if i == 1:
            b = a.copy()
            res[i] = max(a)
            b.remove(res[i])
            rest_elem.append(tuple(b))
            del_elem.append((res[i],))
        elif i == 2:
            b = a.copy()
            res[i], T = FindTwoProducts(a, 'max')
            del_elem.append(T)
            for t in T:
                b.remove(t)
            rest_elem.append(tuple(b))
        elif i > 2:
            b = list(rest_elem[i - 2])

            multmin, Tmin = FindTwoProducts(b, 'min')
            multmax, Tmax = FindTwoProducts(b, 'max')

            T = Tmin if res[i - 2] * multmin > multmax * res[i - 2] else Tmax
            res[i] = max(res[i - 2] * multmin, multmax * res[i - 2])

            del_elem.append(del_elem[i - 2] + T)

            for t in T:
                b.remove(t)
            rest_elem.append(tuple(b))

    if debug == True:
        print(del_elem[-1])

    return res[-1]

print(NmaxMultiply(a, n, True))


#%%[markdown]
# ### the second answer: $O(kn)$ k is the number of collection
# ### $f(k+1) = max\{f{k} \times b_i\}$
# ### $= max\{max\{f(k)\} \times max(a_i), max\{f(k)\} \times min(a_i), min\{f(k)\} \times max(a_i), min\{f(k)\} \times min(a_i) \}$
#%%
n = int(input())
a = list(map(int, input().split()))

def Remove(a:list, l:int):
    b = a.copy()
    b.remove(l)
    return b


def NmaxMultiply2(a, n = 3):
    min_l = [None] * (n + 1)
    max_l = [None] * (n + 1)

    rest_elem = [None] * (n + 1)
    del_elem = [None] * (n + 1)

    for i in range(n + 1):
        if i == 1:
            b = a.copy()
            max_l[i] = max(a)
            min_l[i] = min(a)
            rest_elem[i] = {"min": tuple(Remove(b, min_l[i])),
                            "max": tuple(Remove(b, max_l[i]))}
            del_elem[i] = {"min": (min_l[i],),
                            "max": (max_l[i],)}
        elif i > 1:
            max_set = list(rest_elem[i - 1]["max"])
            min_set = list(rest_elem[i - 1]["min"])
            t = [
                max_l[i - 1] * max(max_set),
                max_l[i - 1] * min(max_set),
                min_l[i - 1] * max(min_set),
                min_l[i - 1] * min(min_set)
            ]
            opt = [max(max_set), min(max_set), max(min_set), min(min_set)]
            max_l[i] = max(t)
            min_l[i] = min(t)

            # memorize the rest element set where the next selection sample.
            rest_elem[i] = {"min": tuple(Remove(min_set if t.index(min_l[i]) > 1 else max_set, opt[t.index(min_l[i])])),
                            "max": tuple(Remove(min_set if t.index(max_l[i]) > 1 else max_set, opt[t.index(max_l[i])]))}
            
            # cache selection items.
            max_del = del_elem[i-1]["max"]
            min_del = del_elem[i-1]["min"]
            del_elem[i] = {"min": (min_del if t.index(min_l[i]) > 1 else max_del) + (opt[t.index(min_l[i])],),
                            "max": (min_del if t.index(max_l[i]) > 1 else max_del) + (opt[t.index(max_l[i])],)}

    print(del_elem[-1]["max"])
    # print(rest_elem[-1]["max"])

    return max_l[-1]


print(NmaxMultiply2(a, n))