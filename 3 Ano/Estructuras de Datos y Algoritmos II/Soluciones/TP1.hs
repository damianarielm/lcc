import Data.List

class Eq p => Punto p where
  dimension :: p -> Int
  coord :: Int -> p -> Double
  dist :: p -> p -> Double
  dist p q = sum [ (^2) $ (coord i p) - (coord i q) | i <- [0 .. (dimension p)-1] ]

data NdTree p = Empty | Node (NdTree p) p (NdTree p) Int deriving (Eq, Ord)
instance Show a => Show (NdTree a) where
  show Empty = "X"
  show (Node l p r e) = "[" ++ show l ++ " < " ++ show p ++ " > " ++ show r ++ "]"

newtype Punto2d = P2d (Double, Double) deriving Eq
instance Show Punto2d where
  show (P2d p) = show p

newtype Punto3d = P3d (Double, Double, Double) deriving Eq
instance Show Punto3d where
  show (P3d p) = show p

instance Punto Punto2d where
  dimension _ = 2
  coord 0 (P2d (x,_)) = x
  coord 1 (P2d (_,y)) = y

instance Punto Punto3d where
  dimension _ = 3
  coord 0 (P3d (x,_,_)) = x
  coord 1 (P3d (_,y,_)) = y
  coord 2 (P3d (_,_,z)) = z

middle :: [a] -> a
middle xs | odd (length xs) = xs !! (div (length xs) 2)
          | otherwise = xs !! (div (length xs) 2)

sortByAxis :: Punto p => Int -> [p] -> [p]
sortByAxis e ps = sortOn (coord e) ps

fromList :: Punto p => [p] -> NdTree p
fromList (p:ps) = fromList' (p:ps) (cycle [0 .. (dimension p)-1]) where
  fromList' [] _      = Empty
  fromList' ps (e:es) = let m = middle $ sortByAxis e ps
                            l = fromList' (delete m [p | p <- ps, coord e p <= coord e m]) es
                            r = fromList' [p | p <- ps, coord e p > coord e m] es
                        in Node l m r e

insertar :: Punto p => p -> NdTree p -> NdTree p
insertar p Empty = Node Empty p Empty 0
insertar p (Node Empty m Empty e)
  | coord e p <= coord e m = Node (Node Empty p Empty ((e+1) `mod` dimension p)) m Empty e
  | otherwise              = Node Empty m (Node Empty p Empty ((e+1) `mod` dimension p)) e
insertar p (Node Empty m r e)
  | coord e p <= coord e m = Node (Node Empty p Empty ((e+1) `mod` dimension p)) m r e
  | otherwise              = Node Empty m (insertar p r) e
insertar p (Node l m Empty e)
  | coord e p <= coord e m = Node (insertar p l) m Empty e
  | otherwise              = Node l m (Node Empty p Empty ((e+1) `mod` dimension p)) e
insertar p (Node l m r e)
  | coord e p <= coord e m = Node (insertar p l) m r e
  | otherwise              = Node l m (insertar p r) e

fromTree :: Punto p => NdTree p -> [p]
fromTree Empty = []
fromTree (Node Empty m Empty _) = [m]
fromTree (Node l m r _) = fromTree l ++ [m] ++ fromTree r

minByAxis :: Punto p => Int -> NdTree p -> p
minByAxis e t = head $ sortByAxis e (fromTree t)

maxByAxis :: Punto p => Int -> NdTree p -> p
maxByAxis e t = head $ reverse $ sortByAxis e (fromTree t)

eliminar :: Punto p => p -> NdTree p -> NdTree p
eliminar p Empty                    = Empty
eliminar p t@(Node Empty m Empty e) | p == m    = Empty
                                    | otherwise = t
eliminar p t@(Node l m Empty e)     | p == m    = let x = maxByAxis e l in Node (eliminar x l) x Empty e
                                    | coord e p <= coord e m = Node (eliminar p l) m Empty e
                                    | otherwise = t
eliminar p t@(Node l m r e)         | p == m    = let x = minByAxis e r in Node l x (eliminar x r) e
                                    | coord e p <= coord e m = Node (eliminar p l) m r e
                                    | otherwise = Node l m (eliminar p r) e

-- Se asume que el primer punto es la esquina inferior izquierda y el restante la esquina superior derecha
type Rect = (Punto2d, Punto2d)

inside :: Punto2d -> Rect -> Bool
inside (P2d (x,y)) (P2d (a,b), P2d (c,d)) = x >= a && x <= c && y <= d && y >= b

ortogonalSearch :: NdTree Punto2d -> Rect -> [Punto2d]
ortogonalSearch Empty _ = []
ortogonalSearch (Node Empty m Empty _) b
  | m `inside` b = [m]
  | otherwise    = []
ortogonalSearch (Node l m r e) b@(p, q)
  | m `inside` b = [m] ++ ortogonalSearch l b ++ ortogonalSearch r b
  | coord e m < coord e p = ortogonalSearch r b
  | coord e m > coord e q = ortogonalSearch l b 
  | otherwise = ortogonalSearch l b ++ ortogonalSearch r b

-- Ejemplo
p0 = P2d (2,3)
p1 = P2d (5,4)
p2 = P2d (9,6)
p3 = P2d (4,7)
p4 = P2d (8,1)
p5 = P2d (7,2)

lista = [p0, p1, p2, p3, p4, p5]
arbol = insertar p5 $ insertar p4 $ insertar p3 $ insertar p2 $ insertar p1 $ insertar p0 Empty
