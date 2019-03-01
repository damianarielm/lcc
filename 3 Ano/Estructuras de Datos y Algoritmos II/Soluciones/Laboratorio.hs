module Lab01 where

import Data.List
import Data.Char

{-
1) Corregir los siguientes programas de modo que sean aceptados por GHCi.
-}

-- a)
not' b = case b of
         True -> False
         False -> True

-- b)
in' [x]         =  []
in' (x:xs)      =  x : (in' xs)
in' []          =  error "empty list"

-- c)
length' []        =  0
length' (_:l)     =  1 + length' l

-- d)
list123 = 1 : 2 : 3 : []

-- e)
[]     ++! ys = ys
(x:xs) ++! ys = x : (xs ++! ys)

-- f)
addToTail x xs = map (+x) (tail xs)

-- g)
listmin xs = (head . sort) xs

-- h) (*)
smap f [] = []
smap f [x] = [f x]
smap f (x:xs) = f x : (smap f xs)

{-
2. Definir las siguientes funciones y determinar su tipo:

a) five, que dado cualquier valor, devuelve 5

b) apply, que toma una función y un valor, y devuelve el resultado de
aplicar la función al valor dado

c) ident, la función identidad

d) first, que toma un par ordenado, y devuelve su primera componente

e) derive, que aproxima la derivada de una función dada en un punto dado

f) sign, la función signo

g) vabs, la función valor absoluto (usando sign y sin usarla)

h) pot, que toma un entero y un número, y devuelve el resultado de
elevar el segundo a la potencia dada por el primero

i) xor, el operador de disyunción exclusiva

j) max3, que toma tres números enteros y devuelve el máximo entre llos

k) swap, que toma un par y devuelve el par con sus componentes invertidas
-}

five :: a -> Int
five _ = 5

apply :: (a -> b) -> a -> b
apply f x = f x

ident :: a -> a
ident x = x

first :: (a, b) -> a
first (x, y) = x

derive :: (Int -> Int) -> Int -> Int
derive = undefined -- COMPLETAR

sign :: Int -> Int
sign x | x == 0 = 0
       | x >  0 = 1
       | x <  0 = -1

vabs :: Int -> Int
vabs x = x * (sign x)

pot :: Int -> Int -> Int
pot x 0 = 1
pot x n = x * (pot x $ n-1)

xor :: Bool -> Bool -> Bool
xor x y = x /= y

max3 :: Int -> Int -> Int -> Int
max3 x y z = maximum [x,y,z]

swap :: (a, b) -> (b, a)
swap (x, y) = (y, x)

{- 
3) Definir una función que determine si un año es bisiesto o no, de
acuerdo a la siguiente definición:

año bisiesto 1. m. El que tiene un día más que el año común, añadido al mes de febrero. Se repite
cada cuatro años, a excepción del último de cada siglo cuyo número de centenas no sea múltiplo
de cuatro. (Diccionario de la Real Academia Espaola, 22ª ed.)

¿Cuál es el tipo de la función definida?
-}

bisiesto :: Int -> Bool
bisiesto = undefined -- COMPLETAR

{-
4)

Defina un operador infijo *$ que implemente la multiplicación de un
vector por un escalar. Representaremos a los vectores mediante listas
de Haskell. Así, dada una lista ns y un número n, el valor ns *$ n
debe ser igual a la lista ns con todos sus elementos multiplicados por
n. Por ejemplo,

[ 2, 3 ] *$ 5 == [ 10 , 15 ].

El operador *$ debe definirse de manera que la siguiente
expresión sea válida:

-}

(*$) xs n = map (*n) xs

v = [1, 2, 3] *$ 2 *$ 4


{-
5) Definir las siguientes funciones usando listas por comprensión:

a) 'divisors', que dado un entero positivo 'x' devuelve la
lista de los divisores de 'x' (o la lista vacía si el entero no es positivo)

b) 'matches', que dados un entero 'x' y una lista de enteros descarta
de la lista los elementos distintos a 'x'

c) 'cuadrupla', que dado un entero 'n', devuelve todas las cuadruplas
'(a,b,c,d)' que satisfacen a^2 + b^2 = c^2 + d^2,
donde 0 <= a, b, c, d <= 'n'

(d) 'unique', que dada una lista 'xs' de enteros, devuelve la lista
'xs' sin elementos repetidos
-}

divisors x = [ y | y <- [1..x], mod x y == 0 ]

matches n xs = [x | x <- xs, x == n]

cuadrupla n = let i = [0..n] in [(a,b,c,d) | a <- i, b <- i, c <- i, d <- i, a^2+b^2 == c^2+d^2]

unique :: [Int] -> [Int]
unique xs = [x | (x,i) <- zip xs [0..], not $ elem x $ take i xs]

{- 
6) El producto escalar de dos listas de enteros de igual longitud
es la suma de los productos de los elementos sucesivos (misma
posición) de ambas listas.  Definir una función 'scalarProduct' que
devuelva el producto escalar de dos listas.

Sugerencia: Usar las funciones 'zip' y 'sum'. -}

scalarProduct xs ys = sum [a*b | (a,b) <- zip xs ys]

{-
7) Definir mediante recursión explícita
las siguientes funciones y escribir su tipo más general:

a) 'suma', que suma todos los elementos de una lista de números

b) 'alguno', que devuelve True si algún elemento de una
lista de valores booleanos es True, y False en caso
contrario

c) 'todos', que devuelve True si todos los elementos de
una lista de valores booleanos son True, y False en caso
contrario

d) 'codes', que dada una lista de caracteres, devuelve la
lista de sus ordinales

e) 'restos', que calcula la lista de los restos de la
división de los elementos de una lista de números dada por otro
número dado

f) 'cuadrados', que dada una lista de números, devuelva la
lista de sus cuadrados

g) 'longitudes', que dada una lista de listas, devuelve la
lista de sus longitudes

h) 'orden', que dada una lista de pares de números, devuelve
la lista de aquellos pares en los que la primera componente es
menor que el triple de la segunda

i) 'pares', que dada una lista de enteros, devuelve la lista
de los elementos pares

j) 'letras', que dada una lista de caracteres, devuelve la
lista de aquellos que son letras (minúsculas o mayúsculas)

k) 'masDe', que dada una lista de listas 'xss' y un
número 'n', devuelve la lista de aquellas listas de 'xss'
con longitud mayor que 'n' -}

suma :: Num a => [a] -> a
suma []     = 0
suma (x:xs) = x + suma xs

alguno :: [Bool] -> Bool
alguno []     = False
alguno (x:xs) = x || alguno xs

todos :: [Bool] -> Bool
todos []     = True
todos (x:xs) = x && todos xs

codes :: [Char] -> [Int]
codes []     = []
codes (x:xs) = (ord x) : codes xs

restos = undefined -- COMPLETAR

cuadrados :: Num a => [a] -> [a]
cuadrados []     = []
cuadrados (x:xs) = x^2 : cuadrados xs

longitudes :: [[a]] -> [Int]
longitudes []       = []
longitudes (xs:xss) = length xs : longitudes xss

orden :: (Num a, Ord a) => [(a,a)] -> [(a,a)]
orden []         = []
orden ((x,y):xs) | x < 3*y = (x,y) : orden xs
                 | otherwise = orden xs

pares = undefined -- COMPLETAR

letras = undefined -- COMPLETAR

masDe = undefined -- COMPLETAR
