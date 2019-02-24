module ListSeq where

import Par
import Seq


instance Seq [] where
  -- Constructores
  emptyS = []
  consS = (:)
  singletonS = (`consS` emptyS)
  tabulateS f n = tabulateS' (\x -> f (n-x)) n where
    tabulateS' _ 0 = emptyS
    tabulateS' f n = let (x,xs) = (f n) ||| (tabulateS' f (n-1))
                     in consS x xs
  fromList = id

  -- Auxiliares
  lengthS = length
  nthS = (!!)
  firstS = head
  isEmptyS = null
  isSingletonS (_:[]) = True
  isSingletonS _ = False
  toList = id

  -- Subsecuencias
  subseqS n m = (takeS (m-n+1)) . (dropS n)
  takeS = take
  dropS = drop
  reverseS = reverse

  -- Modificadores
  appendS = (++)
  updateS []     _ _ = emptyS
  updateS (x:xs) 0 e = consS e xs
  updateS (x:xs) i e = consS x (updateS xs (i-1) e)
  injectS = undefined -- COMPLETAR
  joinS = concat
  zipS = zip
  enumerateS xs = zipS xs [0..]

  -- Listas
  showtS [] = EMPTY
  showtS [x] = ELT x
  showtS xs = let half = div (lengthS xs) 2
                  (l, r) = takeS half xs ||| dropS half xs
              in NODE l r
  showlS [] = NIL
  showlS (x:xs) = CONS x xs

  -- Alto orden
  mapS _ [] = []
  mapS f (x:xs) = let (x',xs') = f x ||| mapS f xs
                  in consS x' xs'
  filterS _ [] = []
  filterS p (x:xs) = let (b, xs') = p x ||| filterS p xs
                     in if b then consS x xs' else xs'
  foldlS = foldl
  foldrS = foldr
  contractS op (x:y:zs) = let (xy, zs') = (op x y) ||| contractS op zs
                          in consS xy zs'
  contractS _ xs = xs
  reduceS op b xs = contractExpandS op (flip const) b (op b) xs
  scanS op b s = contractExpandS op e (emptyS, b) (\x -> (singletonS b, op b x)) s where
   f s s' i = if even i then nthS s' (div i 2)
                        else op (nthS s' (div i 2)) (nthS s (i-1))
   e s (s',t) = (tabulateS (f s s') (lengthS s), t)

  -- Algoritmos genericos
  contractExpandS op e b f []  = b
  contractExpandS op e b f [x] = f x
  contractExpandS op e b f xs  = e xs $ contractExpandS op e b f $ contractS op xs
  dyc m op b xs = case showtS xs of
                  EMPTY    -> b
                  ELT x    -> m x
                  NODE l r -> let (l',r') = dyc m op b l ||| dyc m op b r
                              in op l' r'
  mcrS cmp m r = mapS r . collectS cmp . joinS . mapS m

  -- Ejercicio 6
  mergeS _ [] ys = ys
  mergeS _ xs [] = xs
  mergeS cmp (x:xs) (y:ys) | cmp x y == LT = consS x (mergeS cmp xs (y:ys))
                           | otherwise     = consS y (mergeS cmp (x:xs) ys)
  sortS cmp = (reduceS (mergeS cmp) emptyS) . (mapS singletonS)
  maxES cmp xs = reduceS (\x y -> if cmp x y == LT then y else x) (firstS xs) xs
  maxSS = undefined -- COMPLETAR
  groupS cmp op (x:y:zs) | cmp x y == EQ = let (xy, zs') = op x y ||| groupS cmp op zs
                                           in groupS cmp op $ xy : zs'
                         | otherwise     = x : (groupS cmp op (y:zs))
  groupS _   _  xs       = xs
  collectS cmp xs = let f (x,_) (y,_) = cmp x y
                        g (k,xs) (_,ys) = (k, appendS xs ys)
                    in groupS f g $ sortS f $ mapS (\(a,b) -> (a, singletonS b)) xs
