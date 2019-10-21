from strategy import Algoritmo

class Insercion(Algoritmo): # EstrategiaConcretaB
    def Ordenar(elementos):
        for i in range(1, len(elementos)):
            actual = elementos[i]
            j = i-1
            while j >= 0 and actual < elementos[j]:
                elementos[j+1] = elementos[j]
                j -= 1
            elementos[j+1] = actual
            print(elementos)
