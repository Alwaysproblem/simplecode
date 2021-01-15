arr = [100,-23,-23,404,100,23,23,23,3,404]

# from queue import Queue

def next_node(arr, i, visited):
    r = []
    if i + 1 < len(arr):
        r.append(i + 1)
    
    if i - 1 >= 0:
        r.append(i - 1) 
    
    for j, v in enumerate(arr):
        if j != i and v == arr[i]:
            r.append(j)
    
    return list(set(r).difference(visited))

def bfs(arr, init = 0, tar = len(arr) - 1):
    que = [init]
    p = {}
    solfound = False
    visited = set()

    while len(que) != 0 and solfound is False:
        cur = que.pop(0)
        visited.add(cur)

        if cur == tar:
            solfound = True
        else:
            n_cur = next_node(arr, cur, visited)
            for n in n_cur:
                if n not in que and n not in visited:
                    que.append(n)
                if n not in p:
                    p[n] = cur
    t = tar
    print(t, " -> ")
    while t != init:
        try:
            t = p[t]
        except:
            pass
        print(t, " -> ")

bfs(arr)