import Gnuplot # Libreria de ploteo
import numpy # Manejo de vectores
import sys # Lee archivos

# Lee un grafo de un archivo
def lee_grafo_archivo(file_path):
    vertices = []
    aristas = []
    
    with open(file_path, 'r') as f:
        cantidad = int(f.readline()) # Lee la primer linea

        # Lee vertices
        for i in range(cantidad):
            vertices = vertices + f.readline().split()
            
        # Lee las aristas
        for line in f:
            if len(line.split()) == 3: # Grafo con peso en las aristas
                aristas = aristas + [ ( line.split()[0], line.split()[1], int(line.split()[2]) ) ]
            else: # Grafo sin pesos
                aristas = aristas + [ ( line.split()[0], line.split()[1] ) ]

    grafo = (vertices, aristas)
    return grafo

# Funciones auxiliares
def fa(x,k):
    return (x**2)/k
def fr(x,k):
    return (k**2)/x
def modulo(x):
    return numpy.linalg.norm(x)

# Calcula las fuerzas de repulsion
def calcular_repulsion(vertices, fuerzas, posiciones, k, epsilon):
    for v in vertices:
        fuerzas[v] = numpy.array([0, 0])
        for u in vertices:
            if u != v:
                delta = posiciones[v] - posiciones[u]
                if modulo(delta):
                    fuerzas[v] = fuerzas[v] + (delta / modulo(delta)) * fr(modulo(delta), k)

# Calcula las fuerzas de atraccion
def calcular_atraccion(aristas, fuerzas, posiciones, k, epsilon):
    for arista in aristas:
        v = arista[0]
        u = arista[1]
        delta = posiciones[v] - posiciones[u]
        if modulo(delta):
            fuerzas[v] = fuerzas[v] - (delta / modulo(delta)) * fa(modulo(delta), k)
            fuerzas[u] = fuerzas[u] + (delta / modulo(delta)) * fa(modulo(delta), k)

# Calcula la gravedad
def calcular_gravedad(fuerzas, vertices, posiciones, gravedad):
    for v in vertices:
        fuerzas[v] = fuerzas[v] - posiciones[v] * gravedad

# Calcula las posiciones
def calcular_posiciones(vertices, fuerzas, posiciones, ancho, alto):
    for v in vertices:
        if modulo(fuerzas[v]):
            posiciones[v] = posiciones[v] + (fuerzas[v]/modulo(fuerzas[v]))

        # Impide que los vertices se escapen de la pantalla
        posiciones[v][0] = min(ancho/2, max(-ancho/2, posiciones[v][0]))
        posiciones[v][1] = min(alto/2, max(-alto/2, posiciones[v][1]))

# Crea la ventana
def setwindow(ancho, alto, margen):
    g = Gnuplot.Gnuplot()
    g('set title "GRAFO"')
    g('set terminal wxt size ' + str(ancho) + ', ' + str(alto))
    g('set xrange [' + str((-ancho/2)-margen) + ':' + str((ancho/2)+margen) + ']; set yrange [' + str((-alto/2)-margen) + ':' + str((alto/2)+margen) + ']')
    g('unset key')
    g('plot NaN')
    return g

# Dibuja el grafo
def dibujar(vertices, posiciones, aristas, g, diametro, margen):
    # Dibuja los nodos
    for indice, vertice in enumerate(posiciones.keys()):
        g('set object ' + str(indice+1) + ' circle center ' + str(posiciones[vertice][0]) + ', ' + str(posiciones[vertice][1]) + ' size ' + str(diametro))
        g('set label ' + str(indice+2) + '"' + vertice + '" at ' + str(posiciones[vertice][0]+margen) + ', ' + str(posiciones[vertice][1]))

    # Dibuja las aristas
    for indice, arista in enumerate(aristas):
        u = arista[0]
        v = arista[1]
        midpoint = (posiciones[u] + posiciones[v])/2
        g('set arrow ' + str(indice+len(vertices)*2) + ' nohead from ' + str(posiciones[u][0]) + ', ' + str(posiciones[u][1]) + ' to ' + str(posiciones[v][0]) + ', ' + str(posiciones[v][1]))
        if len(arista) > 2:
            g('set label ' + str(indice+len(vertices)*2+1) + '"' + str(arista[2]) + '" at ' + str(midpoint[0]+margen) + ', ' + str(midpoint[1]))
                
    g('replot')
