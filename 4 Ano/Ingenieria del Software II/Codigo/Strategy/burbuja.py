from strategy import Algoritmo

class Burbuja(Algoritmo): # EstrategiaConcretaA
    def Ordenar(elementos):
        for i in range(len(elementos)):
            for j in range(0, len(elementos)-i-1):
                if elementos[j] > elementos [j+1]:
                    elementos[j], elementos[j+1] = elementos[j+1], elementos[j]
                print(elementos)
