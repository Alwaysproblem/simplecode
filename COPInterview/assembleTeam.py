#%%
# 每三种职业 组成小组 求 最大组成小组的个数
# 例
# 1（询问个数）
#    3    2 2 3
# |职业数|选每种职业的人数|
# 输出：
# 2

#%%


from functools import reduce
import bisect

class PriorityQueue(object):
    def __init__(self, key = lambda x: x):
        self.key = key
        self.data = []
    
    def Enqueue(self, item):
        # heappush(self.data, (self.key(item), item))
        bisect.insort(self.data, (self.key(item), item))

    def Dequeue(self):
        # return heappop(self.data)[1]
        return self.data.pop(0)[1]

    def isEmpty(self):
        return len(self.data) == 0

    def qsize(self):
        return len(self.data)

    def __repr__(self):
        return "PriorityQueue(" + ', '.join(map(str, [i[1] for i in self.data])) + ")"

    # def __str__(self):
    #     return "PriorityQueue(" + ', '.join(map(str, sorted(self.data, key=self.key))) + ")"

    def __iter__(self):
        return self

    def __next__(self):
        if self.isEmpty():
            raise StopIteration
        else:
            return self.Dequeue()

    def __contains__(self, item):
        return any([item == pair[1] for pair in self.data])

    def __getitem__(self, key):
        for _, item in self.data:
            if item == key:
                return item
    
    def __delitem__(self, key):
        for i, (_, item) in enumerate(self.data):
            if item == key:
                self.data.pop(i)

def function(t):
    z = t.pop(0)
    pq = PriorityQueue(key=lambda x: -x)
    if reduce(lambda x, y: x*y, t) == 1 and len(t) == z:
        return len(t) // 3
    else:
        a = [i for i in t if i != 0]
        if len(a) < 3:
            return "None"
        
        for i in a:
            pq.Enqueue(i)
        
        cnt = 0
        while pq.qsize() >= 3:
            s = []
            for _ in range(3):
                s.append(pq.Dequeue())
            
            mm = min(s)
            cnt += mm
            k = [j - mm for j in s]
            for v in k:
                if v != 0:
                    pq.Enqueue(v)

        return cnt



if __name__ == "__main__":
    c = int(input())

    for _ in range(c):
        t = list(map(int, input().split()))
        print(function(t))