def right(node):
    if node == "I":
        return "B", "->", 1
    elif node == "B":
        return "F", "->", 1
    elif node == "E":
        return "JJ", "->", 1
    elif node == "A":
        return "D", "->", 1
    elif node == "C":
        return "H", "->", 1

def left(node):
    if node == "I":
        return "A", "<-", 1
    elif node == "A":
        return "C", "<-", 1
    elif node == "C":
        return "G", "<-", 1
    elif node == "B":
        return "E", "<-", 1
    elif node == "E":
        return "M", "<-", 1

class Ej2:
    def __init__(self):
        self.startState = "I"

    def defaultHeuristic(self, succ):
        return 0

    def alternativeHeuristic(self, succ):
        return 0

    def getSuccessors(self, node):
        return (s for s in (right(node), left(node)) if s != None)

    def isGoalState(self, node):
       return node == "M"
