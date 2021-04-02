from random import choice

def swap(node, i, j, x, y):
    node = [list(x) for x in node]
    node[i][j], node[x][y] = node[x][y], node[i][j]
    return tuple(tuple(x) for x in node)

def getPos(node, number):
    for i, row in enumerate(node):
        if number in row:
            return i, row.index(number)

def moveUp(node):
    i, j = getPos(node, 0)
    if i > 0:
        return swap(node, i, j, i - 1, j), "up", 1

def moveDown(node):
    i, j = getPos(node, 0)
    if i < len(node) - 1:
        return swap(node, i, j, i + 1, j), "down", 1

def moveRight(node):
    i, j = getPos(node, 0)
    if j < len(node) - 1:
        return swap(node, i, j, i, j + 1), "right", 1

def moveLeft(node):
    i, j = getPos(node, 0)
    if j > 0:
        return swap(node, i, j, i, j - 1), "left", 1

class Taken:
    def __init__(self, rows):
        self.ops = ( moveUp, moveDown, moveLeft, moveRight )

        tmp = [[j + rows * i for j in range(rows)] for i in range(rows)]
        self.goalState  = tuple(tuple(x) for x in tmp)

        # Make a start state shuffling the goal
        self.startState = self.goalState
        for i in range(rows * rows * 10):
            tmp = choice(self.ops)(self.startState)
            if tmp:
                self.startState = tmp[0]

    # Misplaced numbers
    def alternativeHeuristic(self, succ):
        total = 0
        for i, row in enumerate(succ):
            for j, element in enumerate(row):
                if element != self.goalState[i][j]:
                    total += 1
        return total

    # Sum of Manhattan distances
    def defaultHeuristic(self, succ):
        total = 0
        for i, row in enumerate(succ):
            for j, element in enumerate(row):
                x, y = getPos(self.goalState, element)
                total += abs(x - i) + abs(y - j)
        return total

    def getSuccessors(self, node):
        return ( op(node) for op in self.ops if op(node) != None )

    def isGoalState(self, node):
        return node == self.goalState
