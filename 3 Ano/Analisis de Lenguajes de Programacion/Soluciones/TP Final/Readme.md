# DSL: Automatas Celulares
## Dependencias
apt install c2hs & cabal install ncurses
## Manual de uso
### Instrucciones de compilacion
#### Generacion de parser
Si por alguna razon desea modificar el modulo de parseo, debera contar con la herramienta de generacion de parses "Happy".
Para instalar dicha herramienta puede utilizar la instruccion:
```shell
cabal install happy
```
Una vez instalada, puede modificar el archivo "Parser.y" y luego generar el parser mediante la instruccion:
```shell
happy Parser.y
```
#### Compilacion
Para compilar el programa basta escribir la orden:
```shell
ghc Main.hs -XRankNTypes
```
### Instrucciones de uso
./Main examples/langton/langton.atm examples/langton/langton.ini
