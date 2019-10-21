from abc import ABC, abstractmethod

class Algoritmo(ABC): # Estrategia
    @abstractmethod
    def Ordenar(elementos): # InterfazAlgoritmo
        pass
