from itertools import product

def put(node, i, j, n):
    if node[i][j] == -1 and n not in node[i] and n not in tuple(zip(*node))[j]:
        newRow  = node[i][:j] + (n,) + node[i][j + 1:]
        newNode = ( node[x] if x != i else newRow for x in range(len(node)) )
        return tuple(newNode), f"{i},{j}:{n}", 1

class Latin:
    def __init__(self, rows):
        self.startState = tuple((-1,) * rows for i in range(rows))

    def alternativeHeuristic(self, succ):
        return 0

    # Empty cells
    def defaultHeuristic(self, succ):
        return sum( row.count(-1) for row in succ )

    def getSuccessors(self, node):
        tmp = product(range(len(node)), range(len(node)), range(len(node)))
        return ( put(node, *args) for args in tmp if put(node, *args) != None )

    def isGoalState(self, node):
        return -1 not in ( e for row in node for e in row )
