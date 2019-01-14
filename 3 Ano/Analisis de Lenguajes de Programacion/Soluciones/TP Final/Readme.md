# DSL: Automatas Celulares
## Descripcion
### Idea general
El presente lenguaje de dominio especifico pretende permitir indicar el comportamiento de automatas celulares, asi como tambien observar su evolucion.

La motivacion principal es proveer una manera sencilla y general de estudiarlos, sin necesidad de tener conocimientos previos de programacion.
### Alcances
Es posible especificar automatas en terminos de vecindad de Moore y vecindad de von Neumann, con funciones de transicion que pueden contar y comprar elementos de su vecindad.
## Dependencias
Para poder correr el programa debera contar con un compilador de *Haskell* y las libreria *UI.NCurses* y *Data.Vector*.
Si utiliza *Ubuntu*, puede instalar el compilador *GHC* con la instruccion:
```shell
sudo apt install ghc
```
Para instalar la libreria *UI.NCurses* necesitara instalar previamente los paquetes *c2hs* y *cabal-install* para lo cual en *Ubuntu* puede utilizar el siguiente comando:
```shell
sudo apt install cabal-install c2hs
```
A continuacion bastara con ejecutar:
```shell
sudo cabal install ncurses vector
```
## Manual de uso
### Instrucciones de compilacion
#### Generacion de parser
Si por alguna razon desea modificar el modulo de parseo, debera contar con la herramienta de generacion de parsers *Happy*.
Para instalar dicha herramienta en *Ubuntu* puede utilizar la instruccion:
```shell
sudo cabal install happy
```
Una vez instalada, puede modificar el archivo *Parser.y* y luego generar el parser mediante la instruccion:
```shell
happy Parser.y
```
#### Programa principal
Para compilar el programa basta escribir la orden:
```shell
ghc Main.hs -O2
```
### Instrucciones de ejecucion
#### Linea de comandos
Si dispone del programa ya compilado puede utilizar la siguiente instruccion para correr el programa:
```shell
./Main AUTOMATA INICIAL [FRONTIER START FRAMES SKIP TIME]
```
donde *AUTOMATA* es el archivo de definicion del automata y *INICIAL* es el estado inicial.
De lo contrario puede ejecutar el programa de la siguiente manera:
```shell
runhaskell Main.hs AUTOMATA INICIAL [FRONTIER START FRAMES SKIP TIME]
```
Sin embargo si opta por esta manera, la perfomance sera notablemente mas baja.
#### Opciones
- *FRONTIER*: Determina el tipo de frontera del automata. Valor por defecto: *Wrap*. Las opciones disponibles son:
  - *Wrap*: Se considera al universo como si sus extremos se tocaran.
  - *Reflect*: Se considera que las celulas fuera del univers reflejan los valores de aquellas dentro del universo.
  - *"Open" 'c'"*: Se considera que las celulas fuera del universo tienen todas el valor fijo *c*.
- *START*: Numero de generacion inicial del automata. Valor por defecto: 0.
- *FRAMES*: Numero de generaciones totales del automata. Valor por defecto: 10900.
- *SKIP*: Salto entre generaciones. Valor por defecto: 0.
- *TIME*: Milisegundos de pausa entre generaciones. Valor por defecto: 0.
## Definicion de automatas
### Gramatica
COMPLETAR.
### Ejemplos
COMPLETAR.
## Informacion adicional
### Distribucion de modulos
COMPLETAR.
### Desiciones de diseño
#### Libreria *UI.NCurses*
Originalmente para mostrar el estado de un autiomata en pantalla se utilizaba la funcion `putStrLn` seguido de `clearScreen`. Sin embargo esto producia perdida de rendimiento y parpadeo en la pantalla.
La libreria *UI.NCurses* no borra la pantalla, sino que redibuja sobre el estado anterior, y ademas solo lo hace en las partes de la pantalla que hayan cambiado. Esto soluciona ambos problemas.
#### Libreria *Data.Vector*
La perfomance ofrecida por las listas secuenciales de Haskell no son adecuadas para este programa, pues es necesario acceder a los diferentes elementos de un estado de manera eficiente.
El acceso en tiempo constante ofrecido por esta libreria es una solucion a los problemas presentados en la implementacion original.
#### Extension *XRankNTypes*
COMPLETAR.
### Bibliografia
Para mayor conocimiento, puede consultar los siguientes articulos de *Wikipedia* que sirvieron de ayuda e inspiracion en este trabajo:
- [Automata Celular](https://es.wikipedia.org/wiki/Aut%C3%B3mata_celular)
- [Vecindad de Moore](https://es.wikipedia.org/wiki/Juego_de_la_vida)
- [Vecindad de von Neumann](https://es.wikipedia.org/wiki/Vecindad_de_von_Neumann)
- [Distancia de Chebyshov](https://es.wikipedia.org/wiki/Distancia_de_Chebyshov)
- [Geometria del taxista](https://es.wikipedia.org/wiki/Geometr%C3%ADa_del_taxista)
- [Juego de la Vida](https://es.wikipedia.org/wiki/Juego_de_la_vida)
- [Hormiga de Langton](https://es.wikipedia.org/wiki/Hormiga_de_Langton)
- [Seeds](https://en.wikipedia.org/wiki/Seeds_(cellular_automaton))
- [Brian's Brain](https://en.wikipedia.org/wiki/Brian%27s_Brain)
- [Wireworld](https://en.wikipedia.org/wiki/Wireworld)

Sirvieron ademas de inspiracion la documentacion de [Happy](https://www.haskell.org/happy/doc/html/sec-using.html) y de [UI.NCurses](http://hackage.haskell.org/package/ncurses), asi como tambien el libro [Learn You a Haskell for Great Good!](http://learnyouahaskell.com/) de Miran Lipovača.
### Acerca del autor
Mi nombre es Damian Ariel, soy estudiante del tercer año de la carrera de Licenciatura en Ciencias de la Computacion en la Facultad de Ciencias Exactas, Ingenieria y Agrimensura de la ciudad de Rosario.

Este trabajo fue presentado en el marco de la catedra de Analisis de Lenguajes de Programacion.
