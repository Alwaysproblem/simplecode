class MyQueue(object):
    def __init__(self):
        self.que = list()

    def peek(self):
        return self.que[0]
        
    def pop(self):
        a = self.que[0]
        del self.que[0]
        return a
        
    def put(self, value):
        self.que.append(value)

queue = MyQueue()
t = int(input())
for line in range(t):
    values = map(int, input().split())
    values = list(values)
    if values[0] == 1:
        queue.put(values[1])        
    elif values[0] == 2:
        queue.pop()
    else:
        print(queue.peek())