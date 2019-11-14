from lista import *

x = Lista(['c','b','z','d','e'])
print("Lista a recorrer: ", x.lista)

print("0 - Reverso")
print("1 - Alfabetico")
print("2 - Regular")

opcion = input("Elija un iterador: ")

if opcion == "0":
    i = x.CrearIterador("Reverso")
elif opcion == "2":
    i = x.CrearIterador("Regular")
elif opcion == "1":
    i = x.CrearIterador("Alfabetico")

print("0 - Primero")
print("1 - Siguiente")
print("2 - HaTerminado")
print("3 - ElementoActual")
print("4 - Salir")

while opcion != "4":
    opcion = input("Ingrese una opcion: ")
    if opcion == "3":
        print(i.ElementoActual())
    elif opcion == "1":
        i.Siguiente()
    elif opcion == "2":
        print(i.HaTerminado())
    elif opcion == "0":
        i.Primero()
