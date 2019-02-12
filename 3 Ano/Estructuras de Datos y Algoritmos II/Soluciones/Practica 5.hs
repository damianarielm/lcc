infix 1 |||
(|||) :: a -> b -> (a,b)
(|||) = (,)

data BTree a = Empty | Node Int (BTree a ) a (BTree a) deriving Show

nodes :: BTree a -> Int
nodes Empty          = 0
nodes (Node s _ _ _) = s

toList :: BTree a -> [a]
toList Empty = []
toList (Node _ l m r) = toList l ++ [m] ++ toList r

nth :: BTree a -> Int -> a
nth (Node _ l m r) n | n+1 <= (nodes l) = nth l n
                     | n == (nodes l)   = m
                     | otherwise        = nth r (n - (nodes l) - 1)

cons :: a -> BTree a -> BTree a
cons x Empty = Node 1 Empty x Empty
cons x (Node s l m r) = Node (s+1) (cons x l) m r

tabulate :: (Int -> a) -> Int -> BTree a
tabulate f 0 = Empty
tabulate f n = let half = div n 2
                   f' = \x -> f (x+half+1)
                   (l,r) = (tabulate f half) ||| (tabulate f' (div (n-1) 2))
               in Node n l (f half) r

map' :: (a -> b) -> BTree a -> BTree b
map' _ Empty          = Empty
map' f (Node s l m r) = let (l', (m', r')) = (map' f l ||| (f m ||| map' f r))
                        in Node s l' m' r'

take' :: Int -> BTree a -> BTree a
take' _ Empty          = Empty
take' 0 _              = Empty
take' n (Node _ l m r) | n == (nodes l) = l
                       | n <  (nodes l) = take' n l
                       | otherwise      = Node n l m (take' (n-(nodes l)-1) r)

drop' :: Int -> BTree a -> BTree a
drop' _ Empty = Empty
drop' 0 t     = t
drop' n (Node s l m r) | n == (nodes l) = Node (s-n) Empty m r
                       | n <  (nodes l) = Node (s-n) (drop' n l) m r
                       | otherwise      = drop' (n-(nodes l)-1) r

data Tree a = E | Leaf a | Join (Tree a) (Tree a) deriving (Show, Eq)

mapT :: (a -> b) -> Tree a -> Tree b
mapT f E          = E
mapT f (Leaf x)   = Leaf (f x)
mapT f (Join l r) = let (l', r') = mapT f l ||| mapT f r
                    in Join l' r'

reduceT :: (a -> a -> a) -> a -> (Tree a) -> a
reduceT _ e E          = e
reduceT _ _ (Leaf x)   = x
reduceT f e (Join l r) = let (l', r') = reduceT f e l ||| reduceT f e r
                         in f l' r'

mapreduce :: (a -> b) -> (b -> b -> b) -> b -> Tree a -> b
mapreduce _ _ e E          = e
mapreduce f _ _ (Leaf x)   = f x
mapreduce f g e (Join l r) = let (l', r') = mapreduce f g e l ||| mapreduce f g e r
                             in g l' r'

mcss :: (Num a, Ord a) => Tree a -> a
mcss t = fst' $ mapreduce f g (0,0,0,0) t where
  fst' (a,_,_,_) = a
  f x = (max x 0, max x 0, max x 0, x)
  g (a,b,c,d) (w,x,y,z) = (maximum [a, w, c+x],max b (d + x),max y (z+c),d+z)

mejorGanancia :: Tree Int -> Int
mejorGanancia t = maxT $ mapT (\(x,y) -> maxT y - x) (conSufijos t)

sufijos :: Tree Int -> Tree (Tree Int)
sufijos t = sufijos' t E where
  sufijos' (Leaf _)   a = Leaf a
  sufijos' (Join l r) a = let (l', r') = sufijos' l (Join r a) ||| sufijos' r a
                          in Join l' r'

conSufijos :: Tree Int -> Tree (Int, Tree Int)
conSufijos = undefined -- COMPLETAR

maxT :: Tree Int -> Int
maxT = reduceT max 0

maxAll :: Tree (Tree Int) -> Int
maxAll = mapreduce maxT max 0

data T a = X | N (T a) a (T a)

altura :: T a -> Int
altura X         = 0
altura (N l m r) = 1 + max (altura l) (altura r)

combinar :: T a -> T a -> T a
combinar X t2         = t2
combinar (N l m r) t2 = N (combinar l r) m t2

filterT :: (a -> Bool) -> T a -> T a
filterT p X         = X
filterT p (N l m r) = let (l',r') = filterT p l ||| filterT p r
                      in if p m then N l' m r' else combinar l' r'

quicksortT :: T Int -> T Int
quicksortT X         = X
quicksortT (N l m r) = let (l', r')  = filterT (<= m) l ||| filterT (<= m) r
                           (l'',r'') = filterT (>  m) l ||| filterT (>  m) r
                           (menores, mayores) = quicksortT (combinar l' r') ||| quicksortT (combinar l'' r'')
                       in N menores m mayores

splitAt' :: BTree a -> Int -> (BTree a, BTree a)
splitAt' t n = take' n t ||| drop' n t

rebalance :: BTree a -> BTree a
rebalance = undefined -- COMPLETAR

-- Ejemplo 1234567
nodo5 = Node 7 nodo4 5 nodo7
nodo4 = Node 4 nodo2 4 Empty
nodo2 = Node 3 nodo1 2 nodo3
nodo1 = Node 1 Empty 1 Empty
nodo3 = Node 1 Empty 3 Empty
nodo7 = Node 2 nodo6 7 Empty
nodo6 = Node 1 Empty 6 Empty
