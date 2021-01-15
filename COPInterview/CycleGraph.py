# assume the graph is like 2 patterns.

# vertex vertex weight

# directly matrix
# from collections import deque

from functools import partial
from math import inf

class Vertex():
    def __init__(self, state):
        self.state = state

class Node(Vertex):
    # just for the search
    def __init__(self, idx, cost = 0, prev = '', state = None):
        super().__init__(state)
        self.index = idx
        self.cost = cost
        self.prev =prev

    def __repr__(self):
        return "Node(" + str(self.index) + ")"

    def __lt__(self, other):
        return self.index < other.index

    def __eq__(self, other):
        return self.index == other.index

    def __hash__(self):
        return hash(self.index)

    def __index__(self):
        return self.index

#%%
class Graph():
    def __init__(self, g, nv, mode = None, Direct = True, optdic = {}, valuedic = {}):
        self.Direct = Direct
        self.mode = mode
        self.numV = nv
        self.mapVertices = [Vertex(state=valuedic[i] if valuedic != {} else None) for i in range(self.numV)]
        self.g= self.encode(g)
        self.opdic = optdic

    def encode(self, g):
        if self.mode == None:
            return g

        elif self.mode == 'Alist':
            graph = {ve : [] for ve in range(self.numV)}
            for v1, v2, weight in g:
                if self.Direct == True:
                    graph[v1].append((v2, weight))
                else:
                    graph[v1].append((v2, weight))
                    graph[v2].append((v1, weight))
            
            return graph
        
        elif self.mode == 'Amatrix':
            graph = [[0] * self.numV for _ in range(self.numV)]
            for v1, v2, weight in g:
                if self.Direct == True:
                    graph[v1][v2] = weight
                else:
                    graph[v1][v2] = weight
                    graph[v2][v1] = weight

            return graph

    def isadjacent(self, v1, v2):
        if self.mode == "Amatrix":
            return self.g[v1][v2] != 0
        else:
            return any([i[0] == v2 for i in self.g[v1]])

    def __repr__(self):
        s = ''
        if self.mode == "Amatrix":
            for i in self.g:
                s += str(i) + '\n' 
            return s
        elif self.mode == "Alist":
            for i in self.g:
                s += str(i) + ": " + str(self.g[i]) + '\n'
            return s
        else:
            raise NotImplementedError()


class MAP(Graph):
    def __init__(self, g, nv, pos, mode = None, Direct = True):
        super().__init__(g, nv, mode, Direct, valuedic=pos)

if __name__ == "__main__":
    nV = 8

    V = {
        0: (0, 0),
        1: (1, 1),
        2: (2, 2),
        3: (1, 0),
        4: (5, 5),
        5: (3, 2),
        6: (2, 1),
        7: (3, 3)
    }

    B = [[0, 1, 1],
         [0, 2, 1], 
         [0, 3, 1], 
         [1, 2, 1], 
         [1, 4, 1], 
         [2, 4, 1], 
         [2, 5, 1], 
         [2, 3, 1],
         [3, 6, 1],
         [6, 7, 1]]

    W = [[0, 1, 2],
         [0, 2, 5], 
         [0, 3, 1], 
         [1, 2, 2], 
         [1, 4, 6], 
         [2, 4, 7], 
         [2, 5, 1], 
         [2, 3, 4],
         [3, 6, 3],
         [6, 7, 4]]

    m = MAP(W, nV, V, mode="Alist")



