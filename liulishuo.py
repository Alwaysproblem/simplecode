# find the directed cycle in the graph
a = eval(input())
print(a)

size = 0

def is_adj(g, a, b):
    return g[a][b]

def extend

def find(a):
    for i in range(len(a)):
        if a[i][i] == 1:
            return 1
