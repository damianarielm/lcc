module Seq where

data TreeView a t = EMPTY | ELT a | NODE t t
data ListView a t = NIL | CONS a t

class Seq s where
   -- Constructores
   emptyS          :: s a
   consS           :: a -> s a -> s a
   singletonS      :: a -> s a
   tabulateS       :: (Int -> a) -> Int -> s a
   fromList        :: [a] -> s a

   -- Auxiliares
   lengthS         :: s a -> Int 
   nthS            :: s a -> Int -> a
   firstS          :: s a -> a
   isEmptyS        :: s a -> Bool
   isSingletonS    :: s a -> Bool
   toList          :: s a -> [a]

   -- Subsecuencias
   subseqS         :: Int -> Int -> s a -> s a
   takeS           :: Int -> s a -> s a
   dropS           :: Int -> s a -> s a
   reverseS        :: s a -> s a

   -- Modificadores
   appendS         :: s a -> s a -> s a
   updateS         :: s a -> Int -> a -> s a
   injectS         :: s a -> s (Int, a) -> s a
   joinS           :: s (s a) -> s a
   zipS            :: s a -> s b -> s (a, b)
   enumerateS      :: s a -> s (a, Int)

   -- Vistas
   showtS          :: s a -> TreeView a (s a)
   showlS          :: s a -> ListView a (s a)

   -- Alto orden
   mapS            :: (a -> b) -> s a -> s b 
   filterS         :: (a -> Bool) -> s a -> s a 
   foldlS          :: (b -> a -> b) -> b -> s a -> b
   contractS       :: (a -> a -> a) -> s a -> s a
   reduceS         :: (a -> a -> a) -> a -> s a -> a
   scanS           :: (a -> a -> a) -> a -> s a -> (s a, a)

   -- Algoritmos genericos
   contractExpandS :: (a -> a -> a) -> (s a -> b -> b) -> b -> (a -> b) -> s a -> b
   dyc             :: (a -> b) -> (b -> b -> b) -> b -> s a -> b
   mcrS            :: (a -> a -> Ordering) -> (b -> s (a, c)) -> ((a, s c) -> d) -> s b -> s d

   -- Ejercicio 6
   mergeS          :: (a -> a -> Ordering) -> s a -> s a -> s a
   sortS           :: (a -> a -> Ordering) -> s a -> s a
   maxES           :: (a -> a -> Ordering) -> s a -> a
   maxSS           :: (a -> a -> Ordering) -> s a -> Int
   groupS          :: (a -> a -> Ordering) -> (a -> a -> a) -> a -> s a -> s a
   collectS        :: (a -> a -> Ordering) -> s (a, b) -> s (a, s b)
