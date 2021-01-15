def mergeInterval(interval: list()):
    if len(interval) <= 1:
        return interval

    n = len(interval)
    inc = sorted(interval, key = lambda x: x[0])

    res = []
    for i in range(n):
        if len(res) != 0 and inc[i][0] <= res[-1][1]:
            res[-1] = [min(inc[i][0], res[-1][0]), max(inc[i][1], res[-1][1])]
        else:
            res.append(inc[i])

    return res

if __name__ == "__main__":
    print(mergeInterval([[1,4],[4,5]]))