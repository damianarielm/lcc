#!/bin/python3

from search       import generalSearch, nullHeuristic
from util         import Stack, Queue, PriorityQueue
from time         import time

from missionaries import Missionaries
from taken        import Taken
from hanoi        import Hanoi
from latin        import Latin
from ej2          import Ej2
from ej11         import Ej11

def mostrarSolucion(*args):
    init = time()
    actions, cost, node = generalSearch(*args)
    print("\nSolucion:", actions)
    print("Estado final:", node)
    print("Costo:", cost)
    print("Tiempo:", time() - init)

def buscar(problem, structure, opcion):
    print("Estado inicial:", problem.startState)
    print("\nBuscando solucion...")

    if opcion != "*":
        heuristic = nullHeuristic
    else:
        heuristic = problem.defaultHeuristic

    mostrarSolucion(problem, structure, heuristic)

    if opcion == "*":
        print("\nHeuristica alternativa...")
        mostrarSolucion(problem, structure, problem.alternativeHeuristic)

def menu():
    print("2: Ejercicio 2")
    print("1: Ejercicio 11")
    print("h: Torres de Hanoi")
    print("t: Taken")
    print("l: Cuadrado latino")
    print("m: Misionarios y canibales")
    opcion = input("Elija un problema: ")

    if opcion == "h":
        opcion = int(input("Ingrese cantidad de discos: "))
        problem = Hanoi(opcion)
    elif opcion == "2":
        problem = Ej2()
    elif opcion == "1":
        opcion = int(input("Ingrese cantidad de fichas blancas: "))
        problem = Ej11(opcion)
    elif opcion == "t":
        opcion = int(input("Ingrese cantidad de filas: "))
        problem = Taken(opcion)
    elif opcion == "l":
        opcion = int(input("Ingrese cantidad de filas: "))
        problem = Latin(opcion)
    elif opcion == "m":
        opcion = int(input("Ingrese cantidad de misionarios: "))
        problem = Missionaries(opcion)
    else:
        print("Error.")
        return
    print()

    print("p: Profundidad (con chequeo de nodos visitados)")
    print("a: Ancho")
    print("u: Costo uniforme")
    print("*: A*")
    opcion = input("Ingrese una busqueda: ")

    if opcion == "p":
        structure = Stack()
    elif opcion == "a":
        structure = Queue()
    elif opcion == "u" or opcion == "*":
        structure = PriorityQueue()
    else:
        print("Error.")
        return
    print()

    buscar(problem, structure, opcion)

menu()
