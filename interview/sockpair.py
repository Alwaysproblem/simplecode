from collections import Counter

# Complete the sockMerchant function below.
def sockMerchant(n, ar):
    C = Counter(ar)
    pair_num = 0
    for num in C.values():
        pair_num += num // 2

    print(pair_num)


if __name__ == "__main__":
    N = int(input())
    arr = map(int, input().split())
    sockMerchant(N, arr)