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
