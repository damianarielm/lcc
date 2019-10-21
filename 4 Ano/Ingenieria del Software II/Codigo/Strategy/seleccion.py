from strategy import Algoritmo

class Seleccion(Algoritmo): # EstrategiaConcretaD
    def Ordenar(elementos):
        for i in range(len(elementos)):
            min_idx = i
            for j in range(i+1, len(elementos)):
                if elementos[min_idx] > elementos[j]:
                    min_idx = j
            elementos[i], elementos[min_idx] = elementos[min_idx], elementos[i]
            print(elementos)
