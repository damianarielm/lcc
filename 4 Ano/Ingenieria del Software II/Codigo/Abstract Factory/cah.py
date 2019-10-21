# Cliente
from espanol import *
from ingles import *
from os import system

def configuracion():
    print("0 - Espanol")
    print("1 - Ingles")
    idioma = Ingles() if input("Elija un idioma: ") == 1 else Espanol()
    cartas = int(input("Ingrese la cantidad de cartas: "))
    system("clear")
    return idioma, cartas

def crearopciones(idioma, cartas):
    opciones = []
    for x in range(cartas):
        opciones.append(idioma.CrearCartaBlanca())
    return opciones

def mostraropciones(opciones):
    for x, opcion in enumerate(opciones):
        print(str(x) + " - " + opcion.Texto())

idioma, cartas = configuracion()

n = idioma.CrearCartaNegra()
n.Mostrar()
print(".\n")

opciones = crearopciones(idioma, cartas)
mostraropciones(opciones)

respuestas = []
for x in range(n.Lugares()):
    respuestas.append(int(input("\nIngrese opcion: ")))

system("clear")

for x in n.Textos():
    if x == None:
        print(opciones[respuestas.pop()].Texto(), end = "")
    else:
        print(x, end = "")
print("\n")
