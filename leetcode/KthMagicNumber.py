
def getKthMagicNumber(k: int) -> int:
        p3 = p5 = p7 = 0
        state = [1] + [0] * (k - 1)

        for i in range(1, k):
            state[i] = min(state[p3] * 3, state[p5] * 5, state[p7] * 7)
            if 3 * state[p3] == state[i]: p3 += 1
            if 5 * state[p5] == state[i]: p5 += 1
            if 7 * state[p7] == state[i]: p7 += 1
        return state[-1]

from heapq import heappop, heappush
def getKthMagicNumber_heap(self, k: int) -> int:
    heap = [1]
    numbers = set()
    # 每次从小顶堆取一个， 取 k 次即可
    cur = 0
    while k:
        cur = heappop(heap)
        if cur not in numbers:
            k -= 1
            heappush(heap, cur * 3)
            heappush(heap, cur * 5)
            heappush(heap, cur * 7)
        numbers.add(cur)
    return cur

if __name__ == '__main__':
    k = int(input())
    print(getKthMagicNumber(k))