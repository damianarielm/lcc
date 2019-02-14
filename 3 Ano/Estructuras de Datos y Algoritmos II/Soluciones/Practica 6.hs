(***) :: (Int, Int, Int, Int) -> (Int, Int, Int, Int) -> (Int, Int, Int, Int)
(***) (a,b,c,d) (w,x,y,z) = (a*w+b*y, a*x+b*z, c*w+d*y, c*x+d*z)

fibSeq :: Int -> [Int]
fibSeq n = take n $ map (\(a,b,c,d) -> a) $ scanl (***) (1,1,1,0) (repeat (1,1,1,0)) 
