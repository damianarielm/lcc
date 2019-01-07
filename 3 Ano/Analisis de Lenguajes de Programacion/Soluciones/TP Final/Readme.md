# DSL: Automatas Celulares
## Dependencias
apt install c2hs & cabal install ncurses
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
```shell
#### Opciones
- *FRONTIER*:
- *START*:
- *FRAMES*:
- *SKIP*:
- *TIME*:
#### Ejemplos
