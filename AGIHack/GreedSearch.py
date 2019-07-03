#%%[markdown]
# remenber all the node that we already extend, just like this table:
#
# |     node      |    1     |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
# | :-----------: | :------: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
# |     cost      | $\infty$ |   5   |   4   |   6   |  11   |   9   |  18   |   9   |  10   |
# | previous node |   ---    |   1   |   1   |   3   |   3   |   2   |   2   |   4   |   8   |
#
# then find path with the recurrsive method that used in the Dijkstra.
# the path for example is 9 -> 8 -> 4 -> 3 -> 1
#%%
#!/usr/bin/python
from queue import PriorityQueue

def citeration(src, dest):
    # TODO manhattan distance
    xs, ys = src
    xd, yd = dest
    if src == dest:
        return 0
    else:
        return abs(xs - xd) + abs(ys - yd)

def GreedySearch(srcpos, destpos, op, ScoreFun = citeration):
    srctup = ("", 0, "", srcpos, "") # cost, id, previous id, pos, opration_name
    visited_set = set()
    order_extend = [srctup]
    pq = PriorityQueue()
    pq.put_nowait(srctup)

    SolFound = False

    while pq.empty() is False and SolFound is False:
        n_ = pq.get_nowait()
        _, id_, _, pos, _ = n_
        # order_extend.append(n_)
        visited_set.add(pos)
        if pos == destpos:
            SolFound = True
        else:
            #extend
            for _, opname in enumerate(op.keys(), 1):

                x, y = op[opname]
                npos = (pos[0] + x, pos[1] + y)

                if npos not in visited_set:
                    nid = len(order_extend)
                    ncost = ScoreFun(npos, destpos)
                    nop = opname
                    nprev_id = id_
                    pq.put_nowait((ncost, nid, nprev_id, npos, nop))
                    order_extend.append((ncost, nid, nprev_id, npos, nop))

    # backtrak for find path
    path_list = []
    point = n_
    prev = point[2]
    while prev != "":
        path_list.append(point)
        point = order_extend[prev]
        prev = point[2]

    # path_list.append(srctup)
    path_list.sort(key = lambda x: x[1])

    path = [i[-1] for i in path_list]

    return path

#%%
def find(grid, src = 'm', dest = 'p'):
    srcpos = None
    destpos = None
    for row, colItem in enumerate(grid):
        if src in set(colItem):
            srcpos = (row, colItem.index(src))
        elif dest in set(colItem):
            destpos = (row, colItem.index(dest))

    return srcpos, destpos

#%%
def displayPathtoPrincess(n, grid):
    #print all the moves here
    opdic = {
        "up": (-1, 0),
        "down": (+1, 0),
        "left": (0, -1),
        "right": (0, +1)
    }

    
    startPos, targetPos = find(grid)
    path = GreedySearch(startPos, targetPos, opdic)

    print(*path, sep='\n')

    # return path


m = int(input())
grid = [] 
for i in range(0, m): 
    grid.append(list(input().strip()))

displayPathtoPrincess(m, grid)