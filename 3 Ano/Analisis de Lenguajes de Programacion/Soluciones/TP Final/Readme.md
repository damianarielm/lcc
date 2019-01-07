# DSL: Automatas Celulares
## Dependencias
Para poder correr el programa debera contar con un compilador de Haskell y la libreria UI.NCurses.
Puede installar el compilador de Haskell GHC con la instruccion:
```shell
apt install gch
```
Para instalar la libreria UI.NCurses necesitara instalar previamente los paquetes c2hs y cabal-install que podra instalar de la siguiente manera:
```shell
apt install cabal-install c2hs
```
A continuacion bastara con ejecutar:
```shell
cabal install ncurses
```
## Manual de uso
### Instrucciones de compilacion
#### Generacion de parser
Si por alguna razon desea modificar el modulo de parseo, debera contar con la herramienta de generacion de parsers "Happy".
Para instalar dicha herramienta puede utilizar la instruccion:
```shell
cabal install happy
```
Una vez instalada, puede modificar el archivo "Parser.y" y luego generar el parser mediante la instruccion:
```shell
happy Parser.y
```
#### Programa principal
Para compilar el programa basta escribir la orden:
```shell
ghc Main.hs -XRankNTypes
```
### Instrucciones de uso
#### Linea de comandos
Si dispone del programa ya compilado puede utilizar la siguiente instruccion para correr el programa:
```shell
./Main AUTOMATA INICIAL [FRONTIER START FRAMES SKIP TIME]
```
donde *AUTOMATA* es el archivo de definicion del automata y *INICIAL* es el estado inicial.
De lo contrario puede ejecutar el programa de la siguiente manera:
```shell
runhaskell --ghc-arg=-XRankNTypes Main.hs AUTOMATA INICIAL [FRONTIER START FRAMES SKIP TIME]
```
#### Opciones
- *FRONTIER*: Determina el tipo de frontera del automata. Las opciones disponibles son:
  - *Wrap*: Se considera al universo como si sus extremos se tocaran.
  - *Reflect*: Se considera que las celulas fuera del univers reflejan los valores de aquellas dentro del universo.
  - *c*: Se considera que las celulas fuera del universo tienen todas el valor fijo *c*.
- *START*: Generacion inicial del automata.
- *FRAMES*: Generaciones totales del automata.
- *SKIP*: Salto entre generaciones.
- *TIME*: Pausa entre generaciones.
#### Ejemplos
## Definicion de automatas
