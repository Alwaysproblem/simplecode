
#%%
# 去掉重复次数 超过 m 的 元素

from collections import Counter

#%%
def solution(n, m, N):
    cnt = Counter(N)
    s = set()

    for i in cnt:
        if cnt[i] > m:
            s.add(i)

    res = []
    for i in N:
        if i not in s:
            res.append(i)

    return res



#%%
if __name__ == "__main__":
    n, m = list(map(int, input().split()))

    N = list(map(int, input().split()))

    print(' '.join(map(str, solution(n, m, N))))
