from abc import ABC, abstractmethod

class Iterador(ABC): # Iterator
    @abstractmethod
    def Primero(self): # Primero
        pass

    @abstractmethod
    def Siguiente(self): # Siguiente
        pass

    @abstractmethod
    def HaTerminado(self): # HaTerminado
        pass

    @abstractmethod
    def ElementoActual(self): #ElementoActual
        pass

class Elementos(ABC): # Agregado
    def CrearIterador(self, tipo):
        pass
