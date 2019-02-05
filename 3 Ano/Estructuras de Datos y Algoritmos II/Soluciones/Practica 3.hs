type Color = (Int, Int, Int)

mezclar :: Color -> Color -> Color
mezclar (a,b,c) (x,y,z) = (avg a x, avg b y, avg c z)
                          where avg x y = div (x+y) 2

type Linea = (String, Int)

vacia :: Linea
vacia = ([], 0)

moverIzq :: Linea -> Linea
moverIzq (s, 0) = (s, 0)
moverIzq (s, p) = (s, p-1)

moverDer :: Linea -> Linea
moverDer (s, p) | p == length s = (s, p)
                | otherwise     = (s, p+1)

moverIni :: Linea -> Linea
moverIni (s, _) = (s, 0)

moverFin :: Linea -> Linea
moverFin (s, _) = (s, length s)

insertar :: Char -> Linea -> Linea
insertar c (s, p) = (take p s ++ [c] ++ drop p s, p+1)

borrar :: Linea -> Linea
borrar (s, p) = (take (p-1) s ++ drop p s, p-1)

data CList a = EmptyCL | CUnit a | Consnoc a (CList a) a

isEmptyCL :: CList a -> Bool
isEmptyCL EmptyCL = True
isEmptyCL _       = False

isCUnit :: CList a -> Bool
isCUnit (CUnit _) = True
isCUnit _         = False

headCL :: CList a -> a
headCL (CUnit x) = x
headCL (Consnoc x _ _) = x

tailCL :: CList a -> CList a
tailCL (CUnit _) = EmptyCL
tailCL (Consnoc x y z) = case y of
                         EmptyCL   -> CUnit z
                         CUnit y'  -> Consnoc y' EmptyCL z
                         otherwise -> Consnoc (headCL y) (tailCL y) z

reverseCL :: CList a -> CList a
reverseCL (Consnoc x y z) = Consnoc z (reverseCL y) x
reverseCL x               = x

initCL :: CList a -> CList a
initCL (CUnit x) = EmptyCL
initCL (Consnoc x EmptyCL z) = CUnit x
initCL (Consnoc x y z) = Consnoc x (initCL y) (lastCL y)

lastCL :: CList a -> a
lastCL (CUnit x)       = x
lastCL (Consnoc _ _ z) = z

inits :: CList a -> CList (CList a)
inits = undefined -- COMPLETAR

lasts :: CList a -> CList (CList a)
lasts = undefined -- COMPLETAR

(+++) :: CList a -> CList a -> CList a
(+++) EmptyCL y = y
(+++) x EmptyCL = x
(+++) (CUnit x) y = Consnoc x (initCL y) (lastCL y)
(+++) x y = Consnoc (headCL x) (tailCL x +++ initCL y) (lastCL y)

concatCL :: CList (CList a) -> CList a
concatCL EmptyCL         = EmptyCL
concatCL (CUnit x)       = x
concatCL (Consnoc x y z) = x +++ (concatCL y) +++ z

data Aexp = Num Int | Prod Aexp Aexp | Div Aexp Aexp

eval :: Aexp -> Int
eval (Num x)    = x
eval (Prod x y) = (eval x) * (eval y)
eval (Div x y)  = div (eval x) (eval y)

seval :: Aexp -> Maybe Int
seval (Num x) = Just x
seval (Prod x y) = do x' <- seval x
                      y' <- seval y
                      return (x' * y')
seval (Div x y) = do x' <- seval x
                     y' <- seval y
                     if y' == 0 then Nothing
                                else return $ div x' y'

data GenTree a = EmptyG | NodeG a [GenTree a]
data BinTree a = EmptyB | NodeB (BinTree a) a (BinTree a)

completo :: a -> Int -> BinTree a
completo = undefined -- COMPLETAR

balanceado :: a -> Int -> BinTree a
balanceado = undefined -- COMPLETAR

g2bt :: GenTree a -> BinTree a
g2bt = undefined -- COMPLETAR

maximumBST :: Ord a => BinTree a -> a
maximumBST (NodeB l x EmptyB) = x
maximumBST (NodeB l x r)     = maximumBST r

checkBST :: Ord a => BinTree a -> Bool
checkBST = undefined -- COMPLETAR

member :: Ord a => BinTree a -> a -> Bool
member EmptyB _ = False
member t@(NodeB l m r) x | x <= m = member' l x m
                         | otherwise = member r x
                         where member' EmptyB x y = x == y
                               member' (NodeB l m r) x y | x <= m = member' l x m
                                                         | otherwise = member' r x y

data ColorRB  = R | B
data RBTree a = EmptyRB | NodeRB ColorRB (RBTree a) a (RBTree a)
