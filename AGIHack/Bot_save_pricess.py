%%

#%%
#!/usr/bin/python
from queue import PriorityQueue

def citeration(src, dest):
    # TODO manhattan distance
    return "inf"

def Astar(srcpos, destpos, op, ScoreFun = citeration):
    srctup = ("", id_, "", srcpos, "") # cost, id, previous id, pos, opration_name
    visited_set = set()
    order_extend = []
    pq = PriorityQueue()
    pq.put_nowait(srctup)

    solFound = False

    while pq.empty() is False or SolFound is False:
        n_ = pq.get_nowait()
        cost_, id_, prev_id, pos, op = n_
        order_extend.append(n_)
        visited_set.add(pos)
        if pos == destpos:
            solFound = True
        else:
            #extend
            extend_list = [n_]
            for i, x, y in enumerate(op.values(), 1):
                nid = len(order_extend) + i
                ncost = ScoreFun(pos, destpos)
                npos = (pos[0] + x, pos[1] + y)
                if npos not in visited_set:
                    





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
        "up": (0, +1),
        "down": (0, -1),
        "left": (+1, 0),
        "right": (-1, 0)
    }

    
    startPos, targetPos = find(grid)
    path = Astar(startPos, targetPos, opdic)

    return path


m = int(input())
grid = [] 
for i in range(0, m): 
    grid.append(list(input().strip()))

displayPathtoPrincess(m,grid)