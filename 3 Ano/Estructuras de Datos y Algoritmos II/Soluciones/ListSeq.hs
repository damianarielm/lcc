module ListSeq where

import Par
import Seq


instance Seq [] where
  -- Constructores
  emptyS = []
  singletonS = (:[])
  tabulateS f n = tabulateS' (\x -> f (n-x)) n where
    tabulateS' _ 0 = []
    tabulateS' f n = let (x,xs) = (f n) ||| (tabulateS' f (n-1))
                     in x:xs
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
  updateS = undefined
  injectS = undefined
  joinS = concat
  zipS = zip
  enumerateS = undefined

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
                  in x':xs'
  filterS _ [] = []
  filterS p (x:xs) = let (b, xs') = p x ||| filterS p xs
                     in if b then x : xs' else xs'
  foldlS = undefined
  contractS op (x:y:zs) = let (xy, zs') = (op x y) ||| contractS op zs
                          in xy : zs'
  contractS _ xs = xs
  reduceS _ b [] = b
  reduceS op b [x] = op b x
  reduceS op b xs = reduceS op b $ contractS op xs
  scanS _ b [] = ([], b)
  scanS op b [x] = ([b], op b x)
  scanS op b s = let (s', total) = scanS op b $ contractS op s
                     f i = if even i then nthS s' (div i 2)
                                     else op (nthS s' (div i 2)) (nthS s (i-1))
                 in (tabulateS f (lengthS s), total)

  -- Algoritmos genericos
  contractExpandS = undefined
  mapReduceS = undefined
  mcrS = undefined

  -- Ejercicio 6
  mergeS = undefined
  sortS = undefined
  maxES = undefined
  maxSS = undefined
  groupS = undefined
  collectS = undefined
