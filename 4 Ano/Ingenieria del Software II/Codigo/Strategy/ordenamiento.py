# Cliente
from random import shuffle
from os import system

from burbuja import Burbuja
from seleccion import Seleccion
from insercion import Insercion
from monticulo import Monticulo

class Elementos(): # Contexto
    def __init__(self, algoritmo):
        self.elementos = []
        self.algoritmo = algoritmo

    def AgregarElemento(self, n): # InterfazContexto
        self.elementos.append(n)

    def Mostrar(self): # InterfazContexto
        print(self.elementos)

    def CambiarAlgoritmo(self, algoritmo): # InterfazContexto
        self.algoritmo = algoritmo

    def Ordenar(self): # InterfazContexto
        self.algoritmo.Ordenar((self.elementos))

    def Desordenar(self): # InterfazContexto
        shuffle(self.elementos)

def menu():
    print("0 - Salir")
    print("1 - Agregar Elemento")
    print("2 - Mostrar Elementos")
    print("3 - Ordenar")
    print("4 - Desordenar")
    print("5 - Cambiar Algoritmo")
    print("6 - Borrar")

def algoritmos():
    print("0 - Burbuja")
    print("1 - Seleccion")
    print("2 - Insercion")
    print("3 - Monticulo")

contexto = Elementos(Burbuja)
menu()

n = 1
while(n != 0):
    n = int(input("Ingrese una opcion: "))
    if n == 1:
        contexto.AgregarElemento(int(input("Ingrese un numero: ")))
    if n == 2:
        contexto.Mostrar()
    if n == 3:
        contexto.Ordenar()
    if n == 4:
        contexto.Desordenar()
    if n == 5:
        algoritmos()
        a = int(input("Ingrese un algoritmo: "))
        if a == 0:
            contexto.CambiarAlgoritmo(Burbuja)
        if a == 1:
            contexto.CambiarAlgoritmo(Seleccion)
        if a == 2:
            contexto.CambiarAlgoritmo(Insercion)
        if a == 3:
            contexto.CambiarAlgoritmo(Monticulo)
    if n == 6:
        system("clear")
        menu()
