######################################################
from math import inf 
def maxSubArraySum(a, size): 

    max_so_far = -inf - 1
    max_ending_here = 0

    for i in range(0, size): 
        max_ending_here = max_ending_here + a[i]
        if max_so_far < max_ending_here:
            max_so_far = max_ending_here
  
        if max_ending_here < 0: 
            max_ending_here = 0 
    return max_so_far
#####################################################
class Stack(object):
    def __init__(self, data = None):
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

class Queue(object):
    def __init__(self, data = None):
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

    def isCycle(self):
        pass

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
    def __init__(self, g: Graph, src:Node, dest:Node):
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
                next_nodes.append(Node(v2, cost=node.cost + weight, prev=node, state=self.graph.mapVertices[v2].state))
        elif self.graph.mode == 'Amatrix':
            nex = [v for v in range(self.graph.numV) if self.graph.isadjacent(node.index, v)]
            for v2 in nex:
                weight = self.graph.g[node][v2]
                next_nodes.append(Node(v2, cost=node.cost + weight, prev=node, state=self.graph.mapVertices[v2].state))
        else:
            raise NotImplementedError()
        return next_nodes
    
    def search(self):
        pass

    def findPath(self):
        p = self.dest.prev
        self.path.push(self.dest)
        while p.prev != "":
            self.path.push(p)
            p = p.prev
        else:
            self.path.push(self.src)

    def displayPath(self):
        print(self, "->".join(map(str, [ve for ve in self.path])), f"Path Cost:{self.dest.cost}", sep=" ")


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
        self.queue = PriorityQueue(key = self.ScoreFun)

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
    def __init__(self, g, src, dest, key = lambda x: x, order = 'min'):
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
                next_nodes.append(Node(v2, cost=node.cost + weight, prev=node, state=self.graph.mapVertices[v2].state))
        elif self.graph.mode == 'Amatrix':
            nex = [v for v in range(self.graph.numV) if self.graph.isadjacent(node.index, v)]
            for v2 in nex:
                weight = self.graph.g[node][v2]
                next_nodes.append(Node(v2, cost=node.cost + weight, prev=node, state=self.graph.mapVertices[v2].state))
        else:
            raise NotImplementedError()
        return sorted(next_nodes, key = self.key, reverse = self.reverse)

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
    def __init__(self, g, src, dest):
        # TODO setting up a table with the node.index
        super().__init__(g, src, dest)
        self.pathTable = [Node(i, cost = inf, state=self.graph.mapVertices[i].state) for i in range(self.graph.numV)]
        self.queue = Queue()
        # self.unvisited = set()

    def relax(self, parent: int, child: int, weight):
        if self.pathTable[parent].cost + weight < self.pathTable[child].cost:
            self.pathTable[child].cost = self.pathTable[parent].cost + weight
            self.pathTable[child].prev = self.pathTable[parent]

    def extend(self, nodeIdx: int):
        next_nodes = []
        if self.graph.mode == 'Alist':
            return self.graph.g[nodeIdx]

        elif self.graph.mode == 'Amatrix':
            return [(v, self.graph.g[nodeIdx][v]) for v in range(self.graph.numV) if self.graph.isadjacent(nodeIdx, v)]
        else:
            raise NotImplementedError()
        return next_nodes


    def search(self):
        self.pathTable[self.src].prev = ''
        self.pathTable[self.src].cost = 0
        self.visited.add(self.src.index)
        self.queue.Enqueue(self.src.index)
        
        while len(self.visited) < self.graph.numV and not self.queue.isEmpty():
            cur_indx = self.queue.Dequeue()
            self.visited.add(cur_indx)
            for n_, weight in self.extend(cur_indx):
                if n_ not in self.visited and n_ not in self.queue:
                    self.queue.Enqueue(n_)
                self.relax(cur_indx, n_, weight)
                    

        self.dest = self.pathTable[self.dest]

    def __repr__(self):
        return "Dijkstra: "
#######################################################
# O(n^2)
# Complete the maximumSum function below.
def maximumSum(a, m):
    maxSum = 0
    n = len(a)
    for i in range(1, n + 1):
        tmpSum = sum(a[:i])
        if tmpSum % m >= maxSum:
            maxSum = tmpSum % m
        for j in range(0, n - i):
            tmpSum = tmpSum - a[j] + a[j + i]
            if tmpSum % m >= maxSum:
                maxSum = tmpSum % m
    return maxSum
#########################################################
# Complete the largestRectangle function below.
def largestRectangle(h):
    s = Stack()
    max_area = 0
    ind = 0

    while ind < len(h):
        if s.isEmpty() or h[s.top] <= h[ind]:
            s.push(ind)
            ind += 1
        else:
            top = s.pop()
            left = 0 if s.isEmpty() else s.top + 1
            max_area = max(max_area, (ind - left) * h[top])

    while not s.isEmpty():
        top = s.pop()
        left = 0 if s.isEmpty() else s.top + 1
        max_area = max(max_area, (ind - left) * h[top])

    return max_area
#########################################################
# Findallsubstring O(n^3)
def findallsubstring(s):
    sub = []
    for ind in range(len(s)):
        for indc in range(ind, len(s)):
            slice_str = s[ind: indc + 1]
            sub.append(slice_str)
    return sub
############################################################
# O(n)
# window slider generator
def WindowSlider(seq, n=2):
    it = iter(seq)
    win = list((next(it, None) for _ in range(n)))
    yield win.copy()
    for e in it:
        win.pop(0)
        win.append(e)
        yield win.copy()
##################################################################
# O(n)
# window slider generator sum
def WindowSlider(seq, n=2):
    it = iter(seq)
    win = list((next(it, None) for _ in range(n)))
    mm = sum(win)
    yield mm
    for e in it:
        tmp = win.pop(0)
        win.append(e)
        mm = mm - tmp + e
        yield mm
##################################################################
