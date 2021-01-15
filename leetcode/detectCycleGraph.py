from collections import defaultdict
 
class Graph():
    def __init__(self, V):
        self.V = V
        self.graph = defaultdict(list)
 
    def addEdge(self, u, v):
        self.graph[u].append(v)
    

    def isCyclic(self):
        color = { u: "white" for u in range(self.V)}
        def backtrace(u, color):

            if color[u] == "gray":
                return True
            
            color[u] = "gray"

            for v in self.graph[u]:
                if color[v] == "gray":
                    return True
                elif color[v] is "white" and backtrace(v, color) == True:
                    return True
                else:
                    pass

            color[u] = "black"
        
            return False
        return backtrace(0, color)

g = Graph(7)
g.addEdge(0, 1)
g.addEdge(1, 2)
g.addEdge(2, 3)
# g.addEdge(4, 1)
# g.addEdge(4, 0)
g.addEdge(3, 4)
g.addEdge(4, 5)
# g.addEdge(2, 6)
g.addEdge(5, 2)

if(g.isCyclic()):
    print ("Graph has a cycle")
else:
    print ("Graph has no cycle")