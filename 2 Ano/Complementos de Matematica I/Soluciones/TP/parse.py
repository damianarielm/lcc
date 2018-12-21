import argparse # Manejo de argumentos

def parse():
	# Definimos los argumentos de lina de comando que aceptamos
	parser = argparse.ArgumentParser()

	# Verbosidad, opcional, False por defecto
	parser.add_argument('-v', '--verbose', 
			action='store_true', 
			help='Muestra mas informacion')

	# Cantidad de iteraciones, opcional, 1500 por defecto
	parser.add_argument('-i', '--iters', type=int, 
			help='Cantidad de iteraciones a efectuar', 
			default=1500)

	# Ancho del dibujo, opcional, 1024 por defecto
	parser.add_argument('-w', '--width', type=int, 
			help='Ancho del dibujo', 
			default=1024)

	# Diametro de los nodos, opcional, 5 por defecto
	parser.add_argument('-d', '--diameter', type=int, 
			help='Diametro de los nodos', 
			default=5)

	# Margen, opcional, 15 por defecto
	parser.add_argument('-m', '--margin', type=int, 
			help='Margen de la ventana', 
			default=15)

	# Alto del dibujo, opcional, 768 por defecto
	parser.add_argument('-l', '--height', type=int, 
			help='Alto del dibujo', 
			default=768)

	# Escala del dibujo, opcional, 1 por defecto
	parser.add_argument('-r', '--ratio', type=float, 
			help='Escala del dibujo', 
			default=0.7)

	# Pausa entre iteraciones, opcional, 0.1 por defecto
	parser.add_argument('-p', '--pause', type=float, 
			help='Pausa entre iteraciones', 
			default=0.1)

	# Pausa final, opcional, 2 por defecto
	parser.add_argument('-n', '--end', type=float, 
			help='Pausa final', 
			default=2)

        # Modulo minimo, opcional, 0 por defecto
	parser.add_argument('-e', '--epsilon', type=float, 
			help='Modulo minimo', 
			default=0)

	# Fuerza minima, opcional, 7 por defecto
	parser.add_argument('-t', '--stop', type=int, 
			help='Fuerza minima', 
			default=7)

	# Salteo de frames por iteracion, opcional, 0 por defecto
	parser.add_argument('-f', '--frame_skip', type=int, 
			help='Salteo de frames por iteracion', 
			default=33)

        # Fuerza de gravedad
	parser.add_argument('-g', '--gravity', type=int, 
			help='Fuerza de gravedad', 
			default=2)

	# Archivo del cual leer el grafo
	parser.add_argument('file_name', 
			help='Archivo del cual leer el grafo a dibujar')

	return parser.parse_args()
