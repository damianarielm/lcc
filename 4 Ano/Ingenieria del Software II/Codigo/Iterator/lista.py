from iterator import *

class Lista(list):
    def __init__(self, lista):
        self.lista = lista
    def CrearIterador(self, tipo):
        if tipo == "Reverso":
            return Reverso(self.lista)
        elif tipo == "Regular":
            return Regular(self.lista)
        elif tipo == "Alfabetico":
            return Alfabetico(self.lista)

class Reverso(Iterador):
    def __init__(self, lista):
        self.lista = lista
        self.posicion = -1
    def Primero(self):
        self.posicion = -1
    def Siguiente(self):
        self.posicion -= 1
    def HaTerminado(self):
        return self.posicion == - len(self.lista)
    def ElementoActual(self):
        return self.lista[self.posicion]

class Regular(Iterador):
    def __init__(self, lista):
        self.lista = lista
        self.posicion = 0
    def Primero(self):
        self.posicion = 0
    def Siguiente(self):
        self.posicion += 1
    def HaTerminado(self):
        return self.posicion == len(self.lista) - 1
    def ElementoActual(self):
        return self.lista[self.posicion]

class Alfabetico(Iterador):
    def __init__(self, lista):
        self.lista = sorted(lista)
        self.posicion = 0
    def Primero(self):
        self.posicion = 0
    def Siguiente(self):
        self.posicion += 1
    def HaTerminado(self):
        return self.posicion == len(self.lista) - 1
    def ElementoActual(self):
        return self.lista[self.posicion]
