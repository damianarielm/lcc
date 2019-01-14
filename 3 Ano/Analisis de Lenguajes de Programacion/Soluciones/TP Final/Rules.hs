module Rules where

import Types
import Matrix
import Data.List (sortBy, groupBy)

chebyshev :: Neighbours
chebyshev (x,y) d = [(x+i,y+j) | i <- [(-d)..d], j <- [(-d)..d], (i,j) /= (0,0)]

manhattan :: Neighbours
manhattan (x,y) d = [(x+i,y+j) | i <- [(-d)..d], j <- [(-d)..d], (abs i)+(abs j) <= d, (i,j) /= (0,0)]

frontier :: Frontier -> Point -> Matrix -> Char
frontier (Open c) (x,y) m
  | outside (x,y) (rows m) (cols m) = c
  | otherwise = m !!! (x,y)
frontier Wrap (x,y) m
  | outside (x,y) (rows m) (cols m) = m !!! wrap (x,y) (rows m) (cols m)
  | otherwise = m !!! (x,y)
frontier Reflect (x,y) m
  | outside (x,y) (rows m) (cols m) = m !!! reflect (x,y) (rows m) (cols m)
  | otherwise = m !!! (x,y)

neighbours :: Frontier -> Char -> Point -> Matrix -> Neighbours -> Int -> Int
neighbours f c (i,j) m n d = length $ filter (== c) [frontier f (x,y) m | (x,y) <- n (i,j) d]

makeTransition :: Frontier -> [[Rule]] -> Transition
makeTransition _ [] (x,y) m = m !!! (x,y)
makeTransition f (conditions@((c,_,_):_):rules) (x,y) m
  | c == (m !!! (x,y)) = tryConditions f conditions rules (x,y) m
  | otherwise          = makeTransition f rules (x,y) m

tryConditions :: Frontier -> [Rule] -> [[Rule]] -> Transition
tryConditions _ [] _ (x,y) m = m !!! (x,y)
tryConditions _ ((_,[],c'):_) _ _ _ = c'
tryConditions f ((z,condition:conditions,c'):moreConditions) rules (x,y) m =
  case condition of
  Chebyshev c d cmp n -> try cmp (neighbours f c (x,y) m chebyshev d) n
  Manhattan c d cmp n -> try cmp (neighbours f c (x,y) m manhattan d) n
  North i cmp c       -> try cmp (frontier f (x-i,y) m) c
  South i cmp c       -> try cmp (frontier f (x+i,y) m) c
  East  i cmp c       -> try cmp (frontier f (x,y+i) m) c
  West  i cmp c       -> try cmp (frontier f (x,y-i) m) c
  NW    i cmp c       -> try cmp (frontier f (x-i,y-i) m) c
  NE    i cmp c       -> try cmp (frontier f (x-i,y+i) m) c
  SW    i cmp c       -> try cmp (frontier f (x+i,y-i) m) c
  SE    i cmp c       -> try cmp (frontier f (x+i,y+i) m) c
  where
  try cmp o1 o2
    | cmp o1 o2 = tryConditions f ((z,conditions,c'):moreConditions) rules (x,y) m
    | otherwise = tryConditions f moreConditions rules (x,y) m

optimize :: [Rule] -> [[Rule]]
optimize xs = groupBy (\(x,_,_) (y,_,_) -> x == y) $ sortBy (\(x,_,_) (y,_,_) -> compare x y) xs
