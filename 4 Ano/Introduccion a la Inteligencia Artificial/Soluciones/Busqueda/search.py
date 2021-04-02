def nullHeuristic(_):
    return 0

def generalSearch(problem, structure, heuristic):
    visited = set()
    structure.push((problem.startState, [], 0), 0)

    while not structure.isEmpty():
        # structure.print()
        node, actions, cost = structure.pop()

        if problem.isGoalState(node):
            return actions, cost, node

        if node not in visited:
            visited.add(node)
            for succ, action, nextCost in problem.getSuccessors(node):
                h = cost + nextCost + heuristic(succ)
                structure.push((succ, actions + [action], cost + nextCost), h)

    return None, None, None
