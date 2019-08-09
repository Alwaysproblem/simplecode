from functools import reduce

a = list(map(int, input().split()))

def NmaxMultiply(a, n = 3):
    b = [abs(i) for i in a]
    c = list(zip(a,b))
    c.sort(key= lambda x: x[1], reverse = True)

    d = c[:n]
    f = c[n:]
    f.sort(key=lambda x:x[0], reverse = True)
    e = len([i[0] for i in d if i[0] < 0])
    if e % 2 == 0:
        return reduce(lambda s, b: s * b, [i[0] for i in d])
    else:
        d.reverse()
        for k, l in d:
            if k < 0:
                break
        d.remove((k, l))
        d.append(f[0])
        return reduce(lambda s, b: s * b, [i[0] for i in d])

print(NmaxMultiply(a))