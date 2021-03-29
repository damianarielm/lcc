from itertools import product

def put(node, i, j):
    if len(node[i]) < len(node):
        tmp = (node[i] + (j,) if x == i else node[x] for x in range(len(node)))
        return tuple(tmp), f"{j}", 1

class Latin:
    def __init__(self, rows):
        self.startState = tuple(() for i in range(rows))

    def alternativeHeuristic(self, succ):
        return 0

    # Repeated numbers and length diference
    def defaultHeuristic(self, succ):
        total = 0
        for n in range(len(self.startState)):
            for t in succ:
                total += len(self.startState) - len(t)
                total += t.count(n) if t.count(n) > 1 else 0

        return total

    def getSuccessors(self, node):
        tmp = product(range(len(node)), range(len(node)))
        return ( put(node, i, j) for i, j in tmp if put(node, i, j) != None )

    def isGoalState(self, node):
        for t in node + tuple(zip(*node)):
            if len(t) != len(self.startState):
                return False
            if len(t) != len(set(t)):
                return False

        return True
