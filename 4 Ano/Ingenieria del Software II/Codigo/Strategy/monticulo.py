from strategy import Algoritmo

class Monticulo(Algoritmo): # EstrategiaConcretaC
    def Ordenar(elementos):
        def heapify(arr, n, i):
            largest = i
            l = 2 * i + 1
            r = 2 * i + 2

            if l < n and arr[i] < arr[l]:
                largest = l

            if r < n and arr[largest] < arr[r]: 
                largest = r 

            if largest != i: 
                arr[i],arr[largest] = arr[largest],arr[i]

                heapify(arr, n, largest)

        n = len(elementos)

        for i in range(n, -1, -1):
            heapify(elementos, n, i)

        for i in range(n-1, 0, -1):
            elementos[i], elementos[0] = elementos[0], elementos[i]
            heapify(elementos, i, 0)
            print(elementos)
