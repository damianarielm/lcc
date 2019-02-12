module ListSeq where

import Par
import Seq

contract op (x:y:zs) = let (xy, zs') = (op x y) ||| contract op zs
                       in xy : zs'
contract _ xs = xs

instance Seq [] where
  emptyS = []
  singletonS = (:[])
  lengthS = length
  nthS = (!!)

  tabulateS f n = tabulateS' (\x -> f (n-x)) n where
    tabulateS' _ 0 = []
    tabulateS' f n = let (x,xs) = (f n) ||| (tabulateS' f (n-1))
                     in x:xs

  mapS _ [] = []
  mapS f (x:xs) = let (x',xs') = f x ||| mapS f xs
                  in x':xs'

  filterS _ [] = []
  filterS p (x:xs) = let (b, xs') = p x ||| filterS p xs
                     in if b then x : xs' else xs'

  appendS = (++)
  takeS = flip take
  dropS = flip drop

  showtS [] = EMPTY
  showtS [x] = ELT x
  showtS xs = let half = div (lengthS xs) 2
                  (l, r) = takeS xs half ||| dropS xs half
              in NODE l r

  showlS [] = NIL
  showlS (x:xs) = CONS x xs

  joinS = concat

  reduceS _ b [] = b
  reduceS op b [x] = op b x
  reduceS op b xs = reduceS op b $ contract op xs

  scanS _ b [] = ([], b)
  scanS op b [x] = ([b], op b x)
  scanS op b s = let (s', total) = scanS op b $ contract op s
                     f i = if even i then nthS s' (div i 2)
                                     else op (nthS s' (div i 2)) (nthS s (i-1))
                 in (tabulateS f (lengthS s), total)

  fromList = id
