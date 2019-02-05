import Data.Char

-- Ejercicio 1
test :: (Eq a, Num a) => (a -> a) -> a -> Bool
test f x = f x == x + 2

esMenor :: Ord a => a -> a -> Bool
esMenor y z = y < z

eq :: Eq a => a -> a -> Bool
eq a b = a == b

showVal :: Show a => a -> String
showVal x = "Valor: " ++ show x

-- Ejercicio 2
ej2a :: Num a => a -> a
ej2a = (+5) -- Suma 5

ej2b :: (Num a, Ord a) => a -> Bool
ej2b = (0<) -- Deterimna si un numero es positivo

ej2c :: String -> String
ej2c = ('a':) -- Agrega una 'a' al principio

ej2d :: String -> String
ej2d = (++ "\n") -- Agrega un salto de linea al final

ej2e :: (Eq a, Num a) => [a] -> [a]
ej2e = filter (== 7) -- Devuelve una lista que solo contiene los sietes

ej2f :: Num a => [[a]] -> [[a]]
ej2f = map (++ [1]) -- Anexa el elemento 1 a cada lista de la lista

-- Ejercicio 3
ej3a1 :: (Int -> Int) -> Int
ej3a1 f = f 0

ej3a2 :: (Int -> Int) -> Int
ej3a2 f = f (f 0)

ej3b1 :: Int -> (Int -> Int)
ej3b1 x = (+x)

ej3b2 :: Int -> (Int -> Int)
ej3b2 x = (*x)

ej3c1 :: (Int -> Int) -> (Int -> Int)
ej3c1 f = negate . f

ej3c2 :: (Int -> Int) -> (Int -> Int)
ej3c2 f = f . f

ej3d1 :: Int -> Bool
ej3d1 x = even x

ej3d2 :: Int -> Bool
ej3d2 x = odd x

ej3e1 :: Bool -> (Bool -> Bool)
ej3e1 x = (&& x)

ej3e2 :: Bool -> (Bool -> Bool)
ej3e2 x = (|| x)

ej3f1 :: (Int, Char) -> Bool
ej3f1 (i, c) = i == (digitToInt c)

ej3f2 :: (Int, Char) -> Bool
ej3f2 = not . ej3f1

ej3g1 :: (Int, Int) -> Int
ej3g1 (x, y) = x + y

ej3g2 :: (Int, Int) -> Int
ej3g2 (x, y) = x * y

ej3h1 :: Int -> (Int, Int)
ej3h1 x = (x, x)

ej3h2 :: Int -> (Int, Int)
ej3h2 x = (negate x, negate x)

ej3i1 :: a -> Bool
ej3i1 x = True

ej3i2 :: a -> Bool
ej3i2 x = False

ej3j1 :: a -> a
ej3j1 x = x

-- Ejercicio 4
ej4a = if true then false else true where false = True; true = False -- False

-- ej4b :: Error sintactico
-- ej4b = if if then then else else

ej4c = False == (5 >= 4) -- False

-- ej4d :: Error de tipos
-- ej4d = 1 < 2 < 3

ej4e = 1 + if ('a' < 'z') then -1 else 0 -- 0

-- ej4f :: Error de tipos
-- ej4f = if fst p then fst p else snd p where p = (True, 2)

ej4g = if fst p then fst p else snd p where p = (True, False) -- True

-- Ejercicio 5
ej5a x = x

ej5b (x, y) = x > y

ej5c (x, y) = (x+y) - y

-- Ejercicio 6
smallest :: Ord a => a -> a -> a -> a
smallest = \x y z -> if x <= y && x <= z then x
                     else if y <= x && y <= z then y
                          else z

second = \_ -> (\x -> x)

andThen = \x y -> if x then y else False

twice = \f x -> f (f x)

flip = \f x y -> f y x

inc = \x -> x+1

-- Ejercicio 7
iff True  y = not y
iff False y = y

alpha x = x

-- Ejercicio 8
f :: Char -> Double
f c = 2

g :: a -> Bool -> Char
g a b = ' '

h :: a -> Bool -> Double
h x y = f (g x y)

-- h' :: Error de tipos
-- h' = f . g

h'' :: a -> Bool -> Double
h'' x = f . (g x) -- == h

-- h''' :: Error de tipos
-- h''' x y = (f . g) x y

-- Ejercicio 9
zip3 [] ys zs = []
zip3 xs [] zs = []
zip3 xs yz [] = []
zip3 (x:xs) (y:ys) (z:zs) = (x, y, z) : (Main.zip3 xs ys zs)

zip3' xs ys zs = flatten $ zip (zip xs ys) zs where
                 flatten [] = []
                 flatten (((x,y),z) : xs) = (x,y,z) : (flatten xs)

-- Ejercicio 10
-- COMPLETAR

-- Ejercicio 11
modulus :: Floating a => [a] -> a
modulus = sqrt . sum . map (^2)

vmod :: Floating a => [[a]] -> [a]
vmod [] = []
vmod (v:vs) = modulus v : vmod vs

-- Ejercicio 12
-- COMPLETAR

-- Ejercicio 13
divisors :: Int -> [Int]
divisors x = [ y | y <- [1..x], mod x y == 0 ]

matches :: Int -> [Int] -> [Int]
matches x xs = [ y | y <- xs, x == y ]

cuadruplas :: Int -> [(Int, Int, Int, Int)]
cuadruplas = undefined -- COMPLETAR

unique :: [Int] -> [Int]
unique = undefined -- COMPLETAR

-- Ejercicio 14
scalarproduct xs ys = let zs = zip xs ys
                      in  sum [x*y | (x,y) <- zs]
