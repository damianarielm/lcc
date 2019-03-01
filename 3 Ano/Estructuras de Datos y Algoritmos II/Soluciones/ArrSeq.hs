module ArrSeq where

import Par
import Seq
import qualified Arr as A

instance Seq A.Arr where
  -- Constructores
  emptyS = A.fromList []
  consS x xs = tabulateS f (lengthS xs + 1) where
    f 0 = x
    f n = nthS xs (n-1)
  singletonS x = fromList [x]
  tabulateS = A.tabulate
  fromList = A.fromList

  -- Auxiliares
  lengthS = A.length
  nthS = (A.!)
  firstS xs = nthS xs 0
  isEmptyS = (==0) . lengthS
  isSingletonS = (==1) . lengthS
  toList xs = case showlS xs of
              NIL -> []
              CONS y ys -> y : (toList ys)

  -- Subsecuencias
  subseqS = undefined -- COMPLETAR
  takeS = (A.subArray 0)
  dropS n xs = A.subArray n (lengthS xs - n) xs
  reverseS = undefined -- COMPLETAR

  -- Modificadores
  appendS xs ys = tabulateS f (lengthS xs + lengthS ys) where
    f n | n <= (lengthS xs - 1) = nthS xs n
        | otherwise = nthS ys (n - lengthS xs)
  updateS = undefined -- COMPLETAR
  injectS = undefined -- COMPLETAR
  joinS = A.flatten
  zipS = undefined -- COMPLETAR
  enumerateS xs = tabulateS (\i -> (nthS xs i,i)) (lengthS xs)

  -- Vistas
  showtS xs | isEmptyS xs = EMPTY
            | isSingletonS xs = ELT $ firstS xs
            | otherwise = let half = div (lengthS xs) 2
                              (l, r) = takeS half xs ||| dropS half xs
                          in NODE l r
  showlS xs | isEmptyS xs = NIL
            | otherwise = let (y, ys) = (nthS xs 0) ||| (dropS 1 xs)
                          in CONS y ys

  -- Alto orden
  mapS f xs = tabulateS (\i -> f (nthS xs i)) (lengthS xs)
  filterS p xs = dyc (\x -> if p x then singletonS x else emptyS) appendS emptyS xs
  foldlS = undefined -- COMPLETAR
  foldrS = undefined -- COMPLETAR
  contractS op xs | lengthS xs > 1 = let (x, xs') = (op (nthS xs 0) (nthS xs 1)) ||| contractS op (dropS 2 xs)
                                     in consS x xs'
                  | otherwise = xs
  reduceS op b xs = contractExpandS op (flip const) b (op b) xs
  scanS op b s = contractExpandS op e (emptyS, b) (\x -> (singletonS b, op b x)) s where
   f s s' i = if even i then nthS s' (div i 2)
                        else op (nthS s' (div i 2)) (nthS s (i-1))
   e s (s',t) = (tabulateS (f s s') (lengthS s), t)

  -- Algoritmos genericos
  contractExpandS op e b f xs | isEmptyS xs = b
                              | isSingletonS xs = f $ nthS xs 0
                              | otherwise = e xs $ contractExpandS op e b f $ contractS op xs
  dyc m op b xs = case showtS xs of
                  EMPTY    -> b
                  ELT x    -> m x
                  NODE l r -> let (l',r') = dyc m op b l ||| dyc m op b r
                              in op l' r'
  mcrS cmp m r = mapS r . collectS cmp . joinS . mapS m

  -- Ejercicio 6
  mergeS = undefined -- COMPLETAR
  sortS cmp = (reduceS (mergeS cmp) emptyS) . (mapS singletonS)
  maxES cmp xs = reduceS (\x y -> if cmp x y == LT then y else x) (firstS xs) xs
  maxSS = undefined -- COMPLETAR
  groupS = undefined -- COMPLETAR
  collectS cmp xs = let f (x,_) (y,_) = cmp x y
                        g (k,xs) (_,ys) = (k, appendS xs ys)
                    in groupS f g $ sortS f $ mapS (\(a,b) -> (a, singletonS b)) xs
