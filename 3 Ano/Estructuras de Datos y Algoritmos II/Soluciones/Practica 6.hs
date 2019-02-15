import Seq
import ListSeq

(***) :: (Int, Int, Int, Int) -> (Int, Int, Int, Int) -> (Int, Int, Int, Int)
(***) (a,b,c,d) (w,x,y,z) = (a*w+b*y, a*x+b*z, c*w+d*y, c*x+d*z)

fibSeq :: Int -> [Int]
fibSeq n = mapS (\(a,b,c,d) -> a) $ fst $ scanS (***) (1,1,1,0) (tabulateS (\_ -> (1,1,1,0)) n)
