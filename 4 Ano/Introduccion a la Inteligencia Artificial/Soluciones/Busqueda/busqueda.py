#!/bin/python3

from time         import time
from util         import Stack, Queue, PriorityQueue

from taken        import Taken
from hanoi        import Hanoi
from latin        import Latin
from missionaries import Missionaries

def nullHeuristic(_):
    return 0

def generalSearch(problem, structure, heuristic):
    visited = set()
    structure.push((problem.startState, [], 0), 0)

    while not structure.isEmpty():
        node, actions, cost = structure.pop()

        if problem.isGoalState(node):
            return actions, cost

        if node not in visited:
            visited.add(node)
            for succ, action, nextCost in problem.getSuccessors(node):
                h = cost + nextCost + heuristic(succ)
                structure.push((succ, actions + [action], cost + nextCost), h)

    return None, None

print("h: Torres de Hanoi")
print("t: Taken")
print("l: Cuadrado latino")
print("m: Misionarios y canibales")
opcion = input("Elija un problema: ")

if opcion == "h":
    opcion = int(input("Ingrese cantidad de discos: "))
    problem = Hanoi(opcion)
elif opcion == "t":
    opcion = int(input("Ingrese cantidad de filas: "))
    problem = Taken(opcion)
elif opcion == "l":
    opcion = int(input("Ingrese cantidad de filas: "))
    problem = Latin(opcion)
elif opcion == "m":
    opcion = int(input("Ingrese cantidad de misionarios: "))
    problem = Missionaries(opcion)

print("s: Stack")
print("q: Queue")
print("p: Priority Queue")
opcion = input("Ingrese una estructura: ")

if opcion == "s":
    structure = Stack()
elif opcion == "q":
    structure = Queue()
elif opcion == "p":
    structure = PriorityQueue()

opcion = input("Usar heuristica s/n: ")
if opcion == "s":
    heuristic = problem.defaultHeuristic
else:
    heuristic = nullHeuristic

print("Estado inicial:", problem.startState)
print("Buscando solucion...")

init = time()
actions, cost = generalSearch(problem, structure, heuristic)
print("\nHeuristica: Principal")
print("Solucion:", actions)
print("Costo:", cost)
print("Tiempo:", time() - init)

if opcion == "s":
    heuristic = problem.alternativeHeuristic
    init = time()
    actions, cost = generalSearch(problem, structure, heuristic)
    print("\nHeuristica: Alternativa")
    print("Solucion:", actions)
    print("Costo:", cost)
    print("Tiempo:", time() - init)
