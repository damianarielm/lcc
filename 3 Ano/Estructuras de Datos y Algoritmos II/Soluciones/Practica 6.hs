import Par
import Seq
import ListSeq

(***) :: (Int, Int, Int, Int) -> (Int, Int, Int, Int) -> (Int, Int, Int, Int)
(***) (a,b,c,d) (w,x,y,z) = (a*w+b*y, a*x+b*z, c*w+d*y, c*x+d*z)

fibSeq :: Seq s => Int -> s Int
fibSeq n = mapS (\(a,b,c,d) -> a) $ fst $ scanS (***) (1,1,1,0) (tabulateS (\_ -> (1,1,1,0)) n)

aguaHist :: Seq s => s Int -> Int
aguaHist xs = let ((maxL, _), (maxR', _)) = scanS max 0 xs ||| (scanS max 0 $ reverseS xs)
                  f i = max 0 $ min (nthS maxL i) (nthS (reverseS maxR') i) - nthS xs i
              in reduceS (+) 0 $ (tabulateS f (lengthS xs) :: [Int])

ejemplo = fromList [2,3,4,7,5,2,3,2,6,4,3,5,2,1] :: [Int]

data Paren = Open | Close

matchParen1 :: Seq s => s Paren -> Bool
matchParen1 = (== (0,0)) . matchParen' where
  matchParen' = let m Open  = (0,1)
                    m Close = (1,0)
                    op (il,jl) (ir,jr) = il + max 0 (ir-jl) ||| max 0 (jl-ir)+jr
                in dyc m op (0,0)

matchParen2 :: Seq s => s Paren -> Bool
matchParen2 = (== (0,0)) . (reduceS op (0,0)) . (mapS m)  where
  m Open  = (0,1)
  m Close = (1,0)
  op (il,jl) (ir,jr) = il + max 0 (ir-jl) ||| max 0 (jl-ir)+jr

matchParen3 :: Seq s => s Paren -> Bool
matchParen3 xs = let m Open  = 1
                     m Close = (-1)
                     (p, t) = scanS (+) 0 $ mapS m xs
                 in t == 0 && reduceS min 0 p == 0

closestPair :: Seq s => s (Int, Int) -> Int
closestPair = undefined -- COMPLETAR

mcss :: (Num a, Ord a, Seq s) => s a -> a
mcss t = fst' $ reduceS g (0,0,0,0) $ mapS f t where
  fst' (a,_,_,_) = a
  f x = (max x 0, max x 0, max x 0, x)
  g (a,b,c,d) (w,x,y,z) = (maximum [a, w, c+x],max b (d + x),max y (z+c),d+z)

sccml :: Seq s => s Int -> Int
sccml xs = mcss $ (tabulateS f (lengthS xs) :: [Int]) where
  f 0 = 0
  f n | nthS xs n > nthS xs (n-1) = 1
      | otherwise = negate (lengthS xs)

ejemplo1 = fromList [9,3,5,1,2,3,4,5,6,1] :: [Int]
ejemplo2 = fromList [5,6,2,3,5,1,9] :: [Int]
ejemplo3 = fromList [1,4,6,7,8,9,10,3] :: [Int]

datosIngreso :: Seq s => s (String, s Int) -> s (Int, Int)
datosIngreso = undefined -- COMPLETAR
                      

countCaract :: Seq s => s (s Char) -> s (Char, Int)
countCaract xss = let m xs = mapS (\c -> (c,1)) xs
                      r (c,xs) = (c, reduceS (+) 0 xs)
                  in mcrS compare m r xss

huffman :: Seq s => s (s Char) -> s (Int, s Char)
huffman = collectS compare . mapS (\(x,y) -> (y,x)) . countCaract
