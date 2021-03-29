def check(m, c, M, C):
    if m < 0 or c < 0 or M < 0 or C < 0:
        return False
    return (m >= c or not m) and (M >= C or not M)

def missionariesL(node):
    m, c, M, C, b = node
    m, M = m + 2, M - 2
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<2M", 1

def missionarieL(node):
    m, c, M, C, b = node
    m, M = m + 1, M - 1
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<1M", 1

def cannibalL(node):
    m, c, M, C, b = node
    c, C = c + 1, C - 1
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<1C", 1

def cannibalsL(node):
    m, c, M, C, b = node
    c, C = c + 2, C - 2
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<2C", 1

def missionariesR(node):
    m, c, M, C, b = node
    m, M = m - 2, M + 2
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "2M>", 1

def missionarieR(node):
    m, c, M, C, b = node
    m, M = m - 1, M + 1
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "1M>", 1

def cannibalR(node):
    m, c, M, C, b = node
    c, C = c - 1, C + 1
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "1C>", 1

def cannibalsR(node):
    m, c, M, C, b = node
    c, C = c - 2, C + 2
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "2C>", 1

def bothR(node):
    m, c, M, C, b = node
    m, c, M, C = m - 1, c - 1, M + 1, C + 1
    if check(m, c, M, C) and b:
        return (m, c, M, C, not b), "MC>", 1

def bothL(node):
    m, c, M, C, b = node
    m, c, M, C = m + 1, c + 1, M - 1, C - 1
    if check(m, c, M, C) and not b:
        return (m, c, M, C, not b), "<MC", 1

class Missionaries:
    def __init__(self, missionaries):
        self.ops =  (missionarieR, missionariesR, missionarieL, missionariesL)
        self.ops += (cannibalR, cannibalsR, cannibalL, cannibalsL, bothR, bothL)
        self.startState = (missionaries, missionaries, 0, 0, True)

    def defaultHeuristic(self, succ):
        return succ[0] + succ[1]

    def alternativeHeuristic(self, succ):
        return 0

    def getSuccessors(self, node):
        return ( op(node) for op in self.ops if op(node) != None )

    def isGoalState(self, node):
        return node[0] == 0 and node[1] == 0
