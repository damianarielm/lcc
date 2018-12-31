module Rules where

import Types
import Matrix

chebyshev :: Neighbours
chebyshev (x,y) d = [(x+i,y+j) | i <- [(-d)..d], j <- [(-d)..d], (i,j) /= (0,0)]

manhattan :: Neighbours
manhattan (x,y) d = [(x+i,y+j) | i <- [(-d)..d], j <- [(-d)..d], (abs i)+(abs j) <= d, (i,j) /= (0,0)]

frontier :: Frontier -> Point -> Matrix -> Char
frontier (Open c) (x,y) m | outside (x,y) (rows m) (cols m) = c
                          | otherwise                       = m !! x !! y
frontier Wrap     (x,y) m | outside (x,y) (rows m) (cols m) = let (a,b) = wrap (x,y) (rows m) (cols m) in m !! a !! b
                          | otherwise                       = m !! x !! y
frontier Reflect  (x,y) m | outside (x,y) (rows m) (cols m) = let (a,b) = reflect (x,y) (rows m) (cols m) in m !! a !! b
                          | otherwise                       = m !! x !! y

neighbours :: Frontier -> Char -> Point -> Matrix -> Neighbours -> Int -> Int
neighbours z c (i,j) m f d = length $ filter (== c) [frontier z (x,y) m | (x,y) <- f (i,j) d]

makeTransition :: Frontier -> [Rule] -> Transition
makeTransition _ [] (x,y) m                                = m !! x !! y
makeTransition _ (([],c'):_) _ _                           = c'
makeTransition f ((condition:conditions,c'):rules) (x,y) m =
  case condition of
  State c             -> try (==) c (m !! x !! y)
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
  moreConditions = ((conditions,c'):rules)
  try cmp o1 o2 | cmp o1 o2 = makeTransition f moreConditions (x,y) m
  try cmp o1 o2 | otherwise = makeTransition f rules          (x,y) m
