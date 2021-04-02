def check(m, c, M, C):
    if m < 0 or c < 0 or M < 0 or C < 0:
        return False
    return (m >= c or not m) and (M >= C or not M)

def missionariesL(m, c, M, C, b):
    m, M = m + 2, M - 2
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<2M", 1

def missionarieL(m, c, M, C, b):
    m, M = m + 1, M - 1
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<1M", 1

def cannibalL(m, c, M, C, b):
    c, C = c + 1, C - 1
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<1C", 1

def cannibalsL(m, c, M, C, b):
    c, C = c + 2, C - 2
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<2C", 1

def missionariesR(m, c, M, C, b):
    m, M = m - 2, M + 2
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "2M>", 1

def missionarieR(m, c, M, C, b):
    m, M = m - 1, M + 1
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "1M>", 1

def cannibalR(m, c, M, C, b):
    c, C = c - 1, C + 1
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "1C>", 1

def cannibalsR(m, c, M, C, b):
    c, C = c - 2, C + 2
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "2C>", 1

def bothR(m, c, M, C, b):
    m, c, M, C = m - 1, c - 1, M + 1, C + 1
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "MC>", 1

def bothL(m, c, M, C, b):
    m, c, M, C = m + 1, c + 1, M - 1, C - 1
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<MC", 1

class Missionaries:
    def __init__(self, missionaries):
        self.startState = (missionaries, missionaries, 0, 0, True)

    def defaultHeuristic(self, succ):
        return succ[0] + succ[1]

    def alternativeHeuristic(self, succ):
        return 0

    def getSuccessors(self, node):
        ops =  (missionarieR, missionariesR, missionarieL, missionariesL)
        ops += (cannibalR, cannibalsR, cannibalL, cannibalsL, bothR, bothL)
        return ( op(*node) for op in ops if op(*node) != None )

    def isGoalState(self, node):
        return node[0] == 0 and node[1] == 0
