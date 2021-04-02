def move12(node):
    x, y, z = node
    total = len(x) + len(y) + len(z)
    if len(x) and len(y) < total and (not y or x[0] < y[0]):
        return (x[1:], x[0:1] + y, z), "1->2", 1

def move13(node):
    x, y, z = node
    total = len(x) + len(y) + len(z)
    if len(x) and len(z) < total and (not z or x[0] < z[0]):
        return (x[1:], y, x[0:1] + z), "1->3", 1

def move21(node):
    x, y, z = node
    total = len(x) + len(y) + len(z)
    if len(y) and len(x) < total and (not x or y[0] < x[0]):
        return (y[0:1] + x, y[1:], z), "2->1", 1

def move23(node):
    x, y, z = node
    total = len(x) + len(y) + len(z)
    if len(y) and len(z) < total and (not z or y[0] < z[0]):
        return (x, y[1:], y[0:1] + z), "2->3", 1

def move31(node):
    x, y, z = node
    total = len(x) + len(y) + len(z)
    if len(z) and len(x) < total and (not x or z[0] < x[0]):
        return (z[0:1] + x, y, z[1:]), "3->1", 1

def move32(node):
    x, y, z = node
    total = len(x) + len(y) + len(z)
    if len(z) and len(y) < total and (not y or z[0] < y[0]):
        return (x, z[0:1] + y, z[1:]), "3->2", 1

class Hanoi:
    def __init__(self, disks):
        self.startState = (tuple(i for i in range(disks)), (), ())
        self.goalState  = ((), (), tuple(i for i in range(disks)))

    def defaultHeuristic(self, succ):
        return len(succ[0]) + len(succ[1])

    def alternativeHeuristic(self, succ):
        return 0

    def getSuccessors(self, node):
        ops = (move12, move13, move21, move23, move31, move32)
        return ( op(node) for op in ops if op(node) != None )

    def isGoalState(self, node):
        return node == self.goalState
