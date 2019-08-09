from functools import reduce

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
            maxProd = min([Ptop1 * Ptop2, Ntop1 * Ntop2])
        
        if maxProd == Ptop1 * Ptop2:
            twoNum = (Ptop1, Ptop2)
        else:
            twoNum = (Ntop1, Ntop2)

    return maxProd, twoNum


def NmaxMultiply(a, n = 3):
    res = [0] * (n + 1)
    delete_elem = [0] # occupy position to convert index starting with 1

    for i in range(1, n + 1):
        if i == 1:
            res[i] = max(a)
            delete_elem.append((res[i],))
        elif i == 2:
            res[i], T = FindTwoProducts(a, 'max')
            delete_elem.append(T)
        elif i > 2:
            b = [k for k in a if k not in delete_elem[i - 2]]
            if res[i - 2] > 0:
                mult, T = FindTwoProducts(b, 'max')
            else:
                mult, T = FindTwoProducts(b, 'min')
            
            res[i] = res[i - 2] * mult

    return res[-1]

print(NmaxMultiply(a))