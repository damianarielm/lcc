module Matrix where

import Types (Point, Matrix, Transition)
import Control.Parallel
import Data.List.Split

rows :: Matrix -> Int
rows = length

cols :: Matrix -> Int
cols = maximum . map length

outside :: Point -> Int -> Int -> Bool
outside (x,y) _ _ | x < 0   || y < 0   = True
outside (x,y) r c | x+1 > r || y+1 > c = True
outside _ _ _     | otherwise          = False

wrap :: Point -> Int -> Int -> Point
wrap (x,y) r c | x < 0     = wrap (r+x, y) r c
               | y < 0     = wrap (x, c+y) r c
               | x+1 > r   = wrap (r-x, y)  r c
               | y+1 > c   = wrap (x, c-y) r c
               | otherwise = (x,y)

reflect :: Point -> Int -> Int -> Point
reflect (x,y) r c | x < 0     = reflect (0, y) r c
                  | y < 0     = reflect (x, 0) r c
                  | x+1 > r   = reflect (r-1, y)  r c
                  | y+1 > c   = reflect (x, c-1) r c
                  | otherwise = (x,y)

fill :: Matrix -> Matrix
fill m = map f m where
       c = cols m
       f r = r ++ (replicate (c - (length r)) ' ')

fromString :: String -> Matrix
fromString = fill . lines

step :: Transition -> Matrix -> Matrix
step f m = let r = (rows m) - 1
               c = (cols m) - 1
           in chunksOf (c+1) $ parallel [(i,j) | i <- [0..r], j <- [0..c]] f m
           -- [ [f (i,j) m | j <- [0..c]] | i <- [0..r] ]

parallel []     _ _ = []
parallel (x:xs) f m = f x m `par` (parallel xs f m) `par` (f x m) : (parallel xs f m)
