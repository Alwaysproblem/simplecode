# assume the graph is like 2 patterns.

# vertex vertex weight

# directly matrix
# from collections import deque

from functools import partial
from math import inf, sqrt


#%%
class Stack(object):

    def __init__(self, data=None):
        if data == None:
            self.data = []
        else:
            self.data = data

    def push(self, data):
        self.data.append(data)

    def pop(self):
        return self.data.pop()

    @property
    def top(self):
        return self.data[-1]

    def isEmpty(self):
        return len(self.data) == 0

    def __repr__(self):
        return "Stack(" + ', '.join(map(str, self.data)) + ")"

    def __str__(self):
        return "Stack(" + ', '.join(map(str, self.data)) + ")"

    def __iter__(self):
        return self

    def __next__(self):
        if self.isEmpty():
            raise StopIteration
        else:
            return self.pop()

    def __contains__(self, item):
        return item in self.data


#%%
class Queue(object):

    def __init__(self, data=None):
        if data == None:
            self.data = []
        else:
            self.data = data

    def Enqueue(self, item):
        self.data.append(item)

    def Dequeue(self):
        return self.data.pop(0)

    def qsize(self):
        return len(self.data)

    def isEmpty(self):
        return len(self.data) == 0

    def __repr__(self):
        return "Queue(" + ', '.join(map(str, self.data)) + ")"

    def __str__(self):
        return "Queue(" + ', '.join(map(str, self.data)) + ")"

    def __iter__(self):
        return self

    def __next__(self):
        if self.isEmpty():
            raise StopIteration
        else:
            return self.Dequeue()

    def __contains__(self, item):
        return item in self.data


#%%
import bisect


class PriorityQueue(object):

    def __init__(self, key=lambda x: x, reverses=False):
        self.key = key
        self.data = []
        self.reverses = reverses

    def Enqueue(self, item):
        # heappush(self.data, (self.key(item), item))
        bisect.insort(self.data, (self.key(item) if not self.reverses else -1 *
                                  self.key(item), item))

    def Dequeue(self):
        # return heappop(self.data)[1]
        return self.data.pop(0)[1]

    def isEmpty(self):
        return len(self.data) == 0

    def qsize(self):
        return len(self.data)

    def __repr__(self):
        return "PriorityQueue(" + ', '.join(map(
            str, [i[1] for i in self.data])) + ")"

    def __str__(self):
        return "PriorityQueue(" + ', '.join(map(
            str, [i[1] for i in self.data])) + ")"

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


# %%
class Vertex(object):

    def __init__(self, state=None):
        self.state = state


class Node(Vertex):
    # just for the search
    def __init__(self, idx, cost=0, prev='', state=None):
        super().__init__(state)
        self.index = idx
        self.cost = cost
        self.prev = prev

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

    def __init__(self, g, nv, mode=None, Direct=True, optdic={}, valuedic={}):
        self.Direct = Direct
        self.mode = mode
        self.numV = nv
        self.mapVertices = [
            Vertex(state=valuedic[i] if valuedic != {} else None)
            for i in range(self.numV)
        ]
        self.g = self.encode(g)
        self.opdic = optdic

    def encode(self, g):
        if self.mode == None:
            return g

        elif self.mode == 'Alist':
            graph = {ve: [] for ve in range(self.numV)}
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

    def isCycle(self, start):
        # if self.mode == "Alist":
        color = {v: "white" for v in self.mapVertices}

        def backtrack(u, color):

            if color[u] == "gray":
                return True

            color[u] = "gray"

            for v in self.g[u]:
                if color[v] == "gray":
                    return True
                elif color[v] == "white" and backtrack(v, color) == True:
                    return True

            color[u] == "black"
            return False

        return backtrack(start, color)

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


#%%
class Search(object):

    def __init__(self, g: Graph, src: Node, dest: Node):
        self.graph = g
        self.src = Node(src, state=self.graph.mapVertices[src].state)
        self.dest = Node(dest, state=self.graph.mapVertices[dest].state)
        self.visited = set()
        self.solfound = False
        self.path = Stack()

    def extend(self, node: Node):
        next_nodes = []
        if self.graph.mode == 'Alist':
            for v2, weight in self.graph.g[node.index]:
                next_nodes.append(
                    Node(v2,
                         cost=node.cost + weight,
                         prev=node,
                         state=self.graph.mapVertices[v2].state))
        elif self.graph.mode == 'Amatrix':
            nex = [
                v for v in range(self.graph.numV)
                if self.graph.isadjacent(node.index, v)
            ]
            for v2 in nex:
                weight = self.graph.g[node][v2]
                next_nodes.append(
                    Node(v2,
                         cost=node.cost + weight,
                         prev=node,
                         state=self.graph.mapVertices[v2].state))
        else:
            raise NotImplementedError()
        return next_nodes

    def search(self):
        pass

    def findPath(self):
        p = self.dest
        while p.prev != "":
            self.path.push(p)
            p = p.prev
        else:
            self.path.push(self.src)

    def displayPath(self):
        print(self,
              "->".join(map(str, [ve for ve in self.path])),
              f"Path Cost:{self.dest.cost}",
              sep=" ")


class BreadthFirstSearch(Search):

    def __init__(self, g, src, dest):
        super().__init__(g, src, dest)
        self.queue = Queue()

    def search(self):
        # self.pathIndexTable[self.src.index] = self.src
        self.queue.Enqueue(self.src)

        while not self.queue.isEmpty() and self.solfound is False:
            cur = self.queue.Dequeue()
            self.visited.add(cur.index)

            if self.dest.index == cur.index:
                self.dest = cur
                # self.pathIndexTable[cur.index] = cur
                self.solfound = True
            else:
                for n_ in self.extend(cur):
                    if n_.index not in self.visited and n_ not in self.queue:
                        self.queue.Enqueue(n_)

    def __repr__(self):
        return "BreadthFirstSearch: "


class BestFirstSearch(BreadthFirstSearch):

    def __init__(self, g, src, dest):
        super().__init__(g, src, dest)
        self.queue = PriorityQueue(key=self.ScoreFun)

    def search(self):
        # self.pathIndexTable[self.src.index] = self.src
        self.queue.Enqueue(self.src)

        while not self.queue.isEmpty() and self.solfound is False:
            cur = self.queue.Dequeue()
            self.visited.add(cur.index)

            if self.dest.index == cur.index:
                self.dest = cur
                self.solfound = True
            else:
                for n_ in self.extend(cur):
                    if n_.index not in self.visited and n_ not in self.queue:
                        self.queue.Enqueue(n_)
                    elif n_ in self.queue:
                        incumbent = self.queue[n_]
                        if self.ScoreFun(n_) < self.ScoreFun(incumbent):
                            del self.queue[incumbent]
                            self.queue.Enqueue(n_)

    def ScoreFun(self, src):
        raise NotImplementedError()


class UniformCost(BestFirstSearch):

    def __init__(self, g, src, dest):
        super().__init__(g, src, dest)
        # self.queue = PriorityQueue(key = self.key)

    def ScoreFun(self, src: Node):
        return src.cost

    def __repr__(self):
        return "UniformCost: "


class BestGreedySearch(BestFirstSearch):

    def __init__(self, g, src, dest, criterion):
        super().__init__(g, src, dest)
        self.criterion = criterion

    def ScoreFun(self, src: Node):
        return self.criterion(src, self.dest)

    def __repr__(self):
        return "BestGreedySearch: "


class Astar(BestFirstSearch):

    def __init__(self, g, src, dest, criterion):
        super().__init__(g, src, dest)
        self.criterion = criterion

    def ScoreFun(self, src: Node):
        return src.cost + self.criterion(src, self.dest)

    def __repr__(self):
        return "Astar: "


class DepthFirstSearch(Search):

    def __init__(self, g, src, dest, key=lambda x: x, order='min'):
        '''
        sorted key for extension. reverse is need 
        '''
        super().__init__(g, src, dest)
        self.stack = Stack()
        self.key = key
        self.reverse = True if order == 'min' else False

    def extend(self, node: Node):
        next_nodes = []
        if self.graph.mode == 'Alist':
            for v2, weight in self.graph.g[node.index]:
                next_nodes.append(
                    Node(v2,
                         cost=node.cost + weight,
                         prev=node,
                         state=self.graph.mapVertices[v2].state))
        elif self.graph.mode == 'Amatrix':
            nex = [
                v for v in range(self.graph.numV)
                if self.graph.isadjacent(node.index, v)
            ]
            for v2 in nex:
                weight = self.graph.g[node][v2]
                next_nodes.append(
                    Node(v2,
                         cost=node.cost + weight,
                         prev=node,
                         state=self.graph.mapVertices[v2].state))
        else:
            raise NotImplementedError()
        return sorted(next_nodes, key=self.key, reverse=self.reverse)

    def search(self):
        # self.pathIndexTable[self.src.index] = self.src
        self.stack.push(self.src)

        while not self.stack.isEmpty() and self.solfound is False:
            cur = self.stack.pop()
            self.visited.add(cur.index)

            if self.dest.index == cur.index:
                self.dest = cur
                # self.pathIndexTable[cur.index] = cur
                self.solfound = True
            else:
                for n_ in self.extend(cur):
                    if n_.index not in self.visited and n_ not in self.stack:
                        self.stack.push(n_)

    def __repr__(self):
        return "DepthFirstSearch: "


class Dijkstra(Search):

    def __init__(self, g, src, dest, priority_queue=True):
        # TODO setting up a table with the node.index
        super().__init__(g, src, dest)
        self.pathTable = [
            Node(i, cost=inf, state=self.graph.mapVertices[i].state)
            for i in range(self.graph.numV)
        ]
        self.queue = Queue() if not priority_queue else PriorityQueue(
            key=lambda x: self.pathTable[x].cost)
        self.priority_queue = priority_queue
        # self.unvisited = set()

    def relax(self, parent: int, child: int, weight):
        if self.pathTable[parent].cost + weight < self.pathTable[child].cost:
            self.pathTable[child].cost = self.pathTable[parent].cost + weight
            self.pathTable[child].prev = self.pathTable[parent]
            if self.priority_queue is False:
                self.queue.Enqueue(child)

    def extend(self, nodeIdx: int):
        if self.graph.mode == 'Alist':
            return self.graph.g[nodeIdx]

        elif self.graph.mode == 'Amatrix':
            return [(v, self.graph.g[nodeIdx][v])
                    for v in range(self.graph.numV)
                    if self.graph.isadjacent(nodeIdx, v)]
        else:
            raise NotImplementedError()

    def search(self):
        self.pathTable[self.src].prev = ''
        self.pathTable[self.src].cost = 0
        self.visited.add(self.src.index)
        self.queue.Enqueue(self.src.index)

        while len(self.visited) < self.graph.numV and not self.queue.isEmpty():
            cur_indx = self.queue.Dequeue()
            self.visited.add(cur_indx)
            for n_, weight in self.extend(cur_indx):
                self.relax(cur_indx, n_, weight)
                if n_ not in self.visited and self.priority_queue:
                    self.queue.Enqueue(n_)

        self.dest = self.pathTable[self.dest]

    def __repr__(self):
        return "Dijkstra: "


class MAP(Graph):

    def __init__(self, g, nv, pos, mode=None, Direct=True):
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

    B = [[0, 1, 1], [0, 2, 1], [0, 3, 1], [1, 2, 1], [1, 4, 1], [2, 4, 1],
         [2, 5, 1], [2, 3, 1], [3, 6, 1], [6, 7, 1]]

    W = [[0, 1, 2], [0, 2, 5], [0, 3, 1], [1, 2, 2], [1, 4, 6], [2, 4, 7],
         [2, 5, 1], [2, 3, 4], [3, 6, 3], [6, 7, 4]]

    m = MAP(W, nV, V, mode="Alist")
    # m = Graph(B, nV, mode="Alist")
    # print(m)
    src = 0
    dest = 5
    # W = [[15, 8, 1], [7, 10, 41], [7, 9, 34], [9, 4, 31], [12, 13, 50],
    #      [14, 3, 52], [4, 11, 99], [4, 7, 86], [10, 13, 57], [9, 6, 10],
    #      [1, 7, 51], [7, 15, 38], [1, 9, 11], [12, 7, 94], [9, 13, 34],
    #      [11, 7, 79], [7, 6, 28], [5, 3, 34], [2, 6, 97], [14, 1, 97],
    #      [6, 10, 90], [12, 10, 37], [13, 3, 73], [11, 14, 7], [15, 1, 39],
    #      [6, 5, 90], [13, 6, 43], [6, 9, 32], [4, 6, 45], [11, 10, 2],
    #      [2, 13, 4], [14, 15, 29], [1, 14, 88], [14, 6, 19], [6, 2, 29],
    #      [3, 14, 72], [1, 15, 4], [11, 5, 2], [6, 7, 56], [8, 7, 88],
    #      [13, 14, 70], [14, 12, 58], [14, 2, 86], [11, 3, 57], [5, 2, 56],
    #      [3, 10, 26], [2, 11, 21], [14, 5, 54], [5, 12, 40], [14, 4, 81],
    #      [15, 2, 99], [5, 7, 57], [13, 12, 5], [4, 9, 60], [12, 15, 48],
    #      [6, 14, 1], [9, 7, 44], [13, 7, 69], [5, 13, 42], [4, 1, 7],
    #      [11, 9, 76], [8, 1, 76], [5, 14, 29], [2, 3, 69], [7, 3, 23],
    #      [12, 14, 28], [11, 4, 85], [10, 1, 10], [15, 12, 36], [1, 11, 69],
    #      [15, 10, 96], [11, 13, 69], [7, 12, 49], [1, 2, 95], [6, 4, 46],
    #      [8, 12, 94], [12, 4, 93], [13, 5, 31], [12, 2, 60], [6, 1, 87],
    #      [4, 14, 20], [5, 11, 89], [4, 15, 88], [4, 10, 21], [1, 6, 5],
    #      [10, 8, 26], [8, 2, 51], [3, 15, 23], [7, 2, 12], [11, 1, 47],
    #      [2, 1, 75], [3, 8, 63], [8, 10, 19], [6, 8, 18], [4, 2, 55],
    #      [14, 11, 80], [10, 3, 73], [3, 5, 22], [12, 3, 61], [1, 13, 33],
    #      [9, 3, 98], [9, 12, 69], [15, 9, 6], [7, 13, 76], [11, 12, 22],
    #      [11, 15, 51], [13, 15, 46], [5, 10, 58], [1, 10, 26], [13, 4, 85],
    #      [7, 14, 58], [5, 8, 46], [11, 6, 32], [10, 9, 41], [9, 14, 35],
    #      [14, 13, 60], [3, 9, 97], [2, 5, 39], [7, 11, 19], [1, 12, 27],
    #      [7, 5, 13], [8, 4, 34], [9, 15, 25], [5, 1, 93], [15, 13, 97],
    #      [14, 9, 35], [8, 6, 67], [9, 5, 39], [13, 11, 35], [7, 4, 21],
    #      [12, 9, 64], [14, 8, 8], [10, 12, 94], [8, 9, 76], [8, 5, 71],
    #      [2, 9, 64], [10, 14, 59], [1, 4, 74], [7, 1, 69], [15, 5, 55],
    #      [6, 15, 80], [13, 8, 84], [8, 13, 63], [8, 3, 91], [10, 4, 87],
    #      [1, 5, 39], [8, 11, 0], [1, 3, 79], [4, 5, 82], [4, 12, 87],
    #      [3, 11, 29], [7, 8, 92], [10, 7, 77], [6, 12, 42], [13, 2, 40],
    #      [9, 10, 13], [4, 13, 65], [2, 4, 34], [3, 13, 44], [2, 14, 69],
    #      [3, 4, 42], [5, 15, 98], [14, 7, 6], [15, 3, 94], [10, 2, 37],
    #      [15, 11, 7], [9, 2, 15], [13, 9, 66], [4, 8, 83], [8, 15, 23],
    #      [13, 1, 50], [6, 13, 57], [2, 10, 37], [10, 6, 38], [2, 7, 45],
    #      [9, 8, 8], [3, 12, 28], [3, 2, 83], [2, 12, 75], [1, 8, 91],
    #      [4, 3, 70], [12, 6, 48], [3, 1, 13], [5, 6, 42], [6, 11, 96],
    #      [3, 6, 22], [15, 6, 34], [11, 8, 43], [15, 7, 40], [9, 11, 57],
    #      [11, 2, 11], [2, 8, 22], [9, 1, 73], [2, 15, 40], [12, 11, 10],
    #      [15, 4, 78], [12, 8, 75], [10, 15, 37], [13, 10, 44], [8, 14, 33],
    #      [3, 7, 82], [5, 4, 46], [12, 5, 79], [15, 14, 43], [10, 5, 65],
    #      [5, 9, 34], [12, 1, 54], [6, 3, 16], [14, 10, 83], [10, 11, 67]]
    # m = Graph(W, 16, mode="Amatrix")
    # src = 11
    # dest = 3

    bfs = BreadthFirstSearch(m, src, dest)
    bfs.search()
    bfs.findPath()
    bfs.displayPath()

    dfs = DepthFirstSearch(m, src, dest, lambda x: x.cost)
    dfs.search()
    dfs.findPath()
    dfs.displayPath()

    ufc = UniformCost(m, src, dest)
    ufc.search()
    ufc.findPath()
    ufc.displayPath()

    Djik = Dijkstra(m, src, dest, priority_queue=True)
    Djik.search()
    Djik.findPath()
    Djik.displayPath()

    def criterion(src: Node, dest: Node):
        xs, ys = src.state
        xd, yd = dest.state
        if src == dest:
            return 0
        else:
            return sqrt((xs - xd)**2 + (ys - yd)**2)

    bgs = BestGreedySearch(m, src, dest, criterion)
    bgs.search()
    bgs.findPath()
    bgs.displayPath()

    a = Astar(m, src, dest, criterion)
    a.search()
    a.findPath()
    a.displayPath()

#%%
