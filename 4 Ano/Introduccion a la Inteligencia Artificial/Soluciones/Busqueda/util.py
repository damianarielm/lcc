import heapq

class Stack:
    def __init__(self):
        self.list = []

    def push(self, item, _):
        self.list.append(item)

    def pop(self):
        return self.list.pop()

    def isEmpty(self):
        return len(self.list) == 0

    def print(self):
        l = list(map(lambda t: t[0], self.list))
        l.reverse()
        print("Top ->", l)

class Queue:
    def __init__(self):
        self.list = []

    def push(self,item,_):
        self.list.insert(0, item)

    def pop(self):
        return self.list.pop()

    def isEmpty(self):
        return len(self.list) == 0

    def print(self):
        l = list(map(lambda t: t[0], self.list))
        l.reverse()
        print("Top ->", l)

class PriorityQueue:
    def  __init__(self):
        self.heap = []

    def push(self, item, priority):
        pair = (priority, item)
        heapq.heappush(self.heap, pair)

    def pop(self):
        (priority, item) = heapq.heappop(self.heap)
        return item

    def isEmpty(self):
        return len(self.heap) == 0

    def print(self):
        l = list(map(lambda t: (t[1][0], t[0]), self.heap))
        print("Top ->", l)
