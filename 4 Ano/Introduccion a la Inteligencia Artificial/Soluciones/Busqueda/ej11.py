from itertools import product

def move(node, i, n):
    if i + n < len(node) and i + n >= 0 and node[i + n] == "V":
        l = list(node)
        l[i], l[i + n] = l[i + n], l [i]
        return tuple(l), f"{i}:{n}", 1 if abs(n) == 1 else abs(n) - 1

class Ej11:
    def __init__(self, n):
        self.startState = ("N",) * n + ("B",) * n + ("V",)

    def alternativeHeuristic(self, succ):
        return 0

    # Missplaced pieces times distance to empty
    def defaultHeuristic(self, succ):
        total = 0
        t = tuple(s for s in succ if s != "V")[:len(succ) // 2]
        for i, e in enumerate(t):
            total += 1 * abs(i - succ.index("V")) if e == "N" else 0
        t = tuple(s for s in succ if s != "V")[len(succ) // 2:]
        for i, e in enumerate(t):
            total += 1 * abs(i - succ.index("V")) if e == "B" else 0
        return total

    def getSuccessors(self, node):
        tmp = product(range(len(node)), (i for i in range(-3,4) if i != 0))
        succs = ( move(node, i, n) for i,n in tmp )
        return ( s for s in succs if s != None )

    def isGoalState(self, node):
        n = (len(node) - 1) // 2
        return tuple(e for e in node if e != "V") == ("B",) * n + ("N",) * n
