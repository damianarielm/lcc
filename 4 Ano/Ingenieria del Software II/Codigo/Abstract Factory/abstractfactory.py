from abc import ABC, abstractmethod

class Idioma(ABC): # FabricaAbstracta
    @abstractmethod
    def CrearCartaBlanca(self): # CrearProductoA
        pass

    @abstractmethod
    def CrearCartaNegra(self): # CrearProductoB
        pass

class CartaBlanca(ABC): # ProductoAbstractoA
    def Texto(self):
        return self.texto

class CartaNegra(ABC): # ProductoAbstractoB
    def Lugares(self):
        return len(list(filter(lambda x: x == None, self.textos)))

    def Textos(self):
        return self.textos

    def Mostrar(self):
        for x in self.textos:
            if x == None:
                print("_______", end = "")
            else:
                print(x, end = "")
