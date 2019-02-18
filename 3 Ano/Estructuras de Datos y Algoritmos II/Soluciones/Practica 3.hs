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

data GenTree a = EmptyG | NodeG a [GenTree a] deriving Show
data BinTree a = EmptyB | NodeB (BinTree a) a (BinTree a)
instance Show a => Show (BinTree a) where
  show EmptyB = "X"
  show (NodeB l m r) = "[" ++ show l ++ " < " ++ show m ++ " > " ++ show r ++ "]"

completo :: a -> Int -> BinTree a
completo _ 0 = EmptyB
completo x n = let t = completo x (n-1)
               in NodeB t x t

balanceado :: a -> Int -> BinTree a
balanceado = undefined -- COMPLETAR

g2bt :: GenTree a -> BinTree a
g2bt EmptyG                      = EmptyB
g2bt (NodeG m xs)                = NodeB (g2bt' xs) m EmptyB
  where g2bt' []                 = EmptyB
        g2bt' ((NodeG m xs):ys)  = NodeB (g2bt' xs) m (g2bt' ys)

-- Ejemplo
nodoa = NodeG 'a' [nodob, nodoc, nodod, nodoe, nodof, nodog]
nodob = NodeG 'b' [nodoq, nodoh, nodoi]
nodoq = NodeG 'q' [nodom, nodon]
nodom = NodeG 'm' []
nodon = NodeG 'n' []
nodoh = NodeG 'h' []
nodoi = NodeG 'i' []
nodoc = NodeG 'c' []
nodod = NodeG 'd' []
nodoe = NodeG 'e' [nodoj, nodok]
nodoj = NodeG 'j' [nodoo]
nodoo = NodeG 'o' []
nodok = NodeG 'k' [nodop]
nodop = NodeG 'p' []
nodof = NodeG 'f' []
nodog = NodeG 'g' [nodol]
nodol = NodeG 'l' []

maximumBST :: Ord a => BinTree a -> a
maximumBST (NodeB _ x EmptyB) = x
maximumBST (NodeB _ _ r)      = maximumBST r

value :: BinTree a -> a
value (NodeB _ x _) = x

checkBST :: Ord a => BinTree a -> Bool
checkBST EmptyB                  = True
checkBST (NodeB EmptyB m EmptyB) = True
checkBST (NodeB EmptyB m r)      = checkBST r && m <  value r
checkBST (NodeB l m EmptyB)      = checkBST l && m >= value l
checkBST (NodeB l m r)           = checkBST l && checkBST r && m < value r && m >= value l

member :: Ord a => BinTree a -> a -> Bool
member EmptyB _ = False
member t@(NodeB l m r) x | x <= m = member' l x m
                         | otherwise = member r x
                         where member' EmptyB x y = x == y
                               member' (NodeB l m r) x y | x <= m = member' l x m
                                                         | otherwise = member' r x y

data ColorRB  = R | B
data RBTree a = EmptyRB | NodeRB ColorRB (RBTree a) a (RBTree a)

insert :: Ord a => a -> RBTree a -> RBTree a
insert x t = makeBlack (insert' x t)
  where insert' x EmptyRB = NodeRB R EmptyRB x EmptyRB
        insert' x t@(NodeRB c l m r) | x <  m = balance c (insert' x l) m r -- COMPLETAR
                                     | x >  m = balance c l m (insert' x r) -- COMPLETAR
                                     | x == m = t
        makeBlack EmptyRB            = EmptyRB
        makeBlack (NodeRB _ l m r)   = NodeRB B l m r

balance :: ColorRB -> RBTree a -> a -> RBTree a -> RBTree a
balance B (NodeRB R (NodeRB R a x b) y c) z d = NodeRB R (NodeRB B a x b) y (NodeRB B c z d)
balance B (NodeRB R a x (NodeRB R b y c)) z d = NodeRB R (NodeRB B a x b) y (NodeRB B c z d)
balance B a x (NodeRB R (NodeRB R b y c) z d) = NodeRB R (NodeRB B a x b) y (NodeRB B c z d)
balance B a x (NodeRB r b y (NodeRB R c z d)) = NodeRB R (NodeRB B a x b) y (NodeRB B c z d)
balance c l a r = NodeRB c l a r

lbalance = undefined -- COMPLETAR
rbalance = undefined -- COMPLETAR

data Heap a = E | N Int (Heap a) a (Heap a) deriving Show

merge :: Ord a => Heap a -> Heap a -> Heap a
merge h1 E = h1
merge E h2 = h2
merge h1@(N _ l1 m1 r1) h2@(N _ l2 m2 r2) | m1 <= m2 = makeH m1 l1 (merge r1 h2)
                                          | m1 >  m2 = makeH m2 l2 (merge h1 r2)

rank :: Heap a -> Int
rank E = 0
rank (N r _ _ _) = r

makeH :: a -> Heap a -> Heap a -> Heap a
makeH x h1 h2 | rank h1 >= rank h2 = N (rank h2 + 1) h1 x h2
              | otherwise          = N (rank h1 + 1) h2 x h1

fromList :: Ord a => [a] -> Heap a
fromList []                = E
fromList [x]               = N 1 E x E
fromList (x:y:zs) | x <= y = merge (N 1 (N 1 E y E) x E) (fromList zs)
                  | x >  y = merge (N 1 (N 1 E x E) y E) (fromList zs)
