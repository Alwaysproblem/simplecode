#%%
#!/usr/bin/python
from queue import PriorityQueue


def displayPathtoPrincess(n, grid):
    #print all the moves here
    opdic = {
        "up": (0, +1),
        "down": (0, -1),
        "left": (+1, 0),
        "right": (-1, 0)
    }

    def citeration(src, dest):
        # TODO manhattan distance
        return -1
    
    


    # A-star search
    PQ = PriorityQueue()


m = int(input())
grid = [] 
for i in range(0, m): 
    grid.append(input().strip())

displayPathtoPrincess(m, grid)