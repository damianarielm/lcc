#! /usr/bin/python

# sudo apt install gnuplot
# pip install numpy
# http://gnuplot-py.sourceforge.net/

from numpy import array # Manejo de vectores
from time import sleep # Funcion Sleep
from math import sqrt # Raiz cuadrada
from random import randint # Numeros aleatorios
from parse import parse # Manejo de linea de comandos
from aux import *

def run_layout(grafo, ancho, alto, diametro, margen, iteraciones, tamano, pausa, fin, step, verbose, stop, epsilon, gravedad):
    '''
    Dado un grafo (en formato de listas), aplica el algoritmo de 
    Fruchtermann-Reingold para obtener (y mostrar) un layout
    '''
    # Variables auxiliares
    vertices, aristas = grafo
    posiciones = {}
    fuerzas = {}
    k = sqrt(ancho * alto / len(vertices)) * tamano

    # Inicializa la ventana de dibujo
    if step:
        g = setwindow(ancho, alto, margen)

    # Inicializa vertices en posiciones aleatorias
    for vertice in vertices:
        posiciones[vertice] = array([randint(-ancho/2,ancho/2), randint(-alto/2,alto/2)])

    if verbose:
        print "Posiciones iniciales:"
        print "====================="
        print "Vertice:\tPosicion:"
        for v in posiciones:
            print v, "\t\t", posiciones[v]
        
    # Bucle principal
    for i in range(iteraciones):
        calcular_repulsion(vertices, fuerzas, posiciones, k, epsilon)
        calcular_atraccion(aristas, fuerzas, posiciones, k, epsilon)
        calcular_gravedad(fuerzas, vertices, posiciones, gravedad)
        calcular_posiciones(vertices, fuerzas, posiciones, ancho, alto)

        # Detiene el bucle si las fuerzas son debiles
        total = 0
        for vertice in vertices:
            total += modulo(fuerzas[vertice])
        if total/len(vertices) < stop:
            if verbose:
                print "Finalizado por promedio de fuerzas debil:", total/len(vertices)
            break          

        # Dibuja el frame
        if step and not (i % step):
            if verbose:
              print "\nITERACION " + str(i)
              print "=============="
              print "Fuerzas promedio: " + str(total/len(vertices))
              print "Fuerzas:\t\tPosiciones:"
              for vertice, fuerza in fuerzas.items():
                print vertice + " [" + str(int(fuerza[0])) + "  " + str(int(fuerza[1])) + "]\t\t[" + str(int(posiciones[vertice][0])) + " " + str(int(posiciones[vertice][1])) + "]"

            dibujar(vertices, posiciones, aristas, g, diametro, margen)
            sleep(pausa)

    # Dibujo final
    if not step:
        g = setwindow(ancho, alto, margen)
    dibujar(vertices, posiciones, aristas, g, diametro, margen)
    sleep(fin)
   
def main():
    a = parse() # Manejo de linea de comandos

    # Ejecutamos el layout
    grafo = lee_grafo_archivo(a.file_name)
    run_layout(grafo, a.width, a.height, a.diameter, a.margin, a.iters, a.ratio, a.pause, a.end, a.frame_skip, a.verbose, a.stop, a.epsilon, a.gravity)
    return
 
if __name__ == "__main__":
    main()
