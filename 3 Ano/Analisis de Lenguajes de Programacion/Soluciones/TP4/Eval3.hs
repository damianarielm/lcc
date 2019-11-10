module Eval3 (eval) where

import AST
import Control.Applicative (Applicative(..))
import Control.Monad       (liftM, ap)  

-- Estados
type Env = [(Variable,Int)]

-- Estado nulo
initState :: Env
initState = []

-- Evalua un programa en el estado nulo
eval :: Comm -> Env
eval = undefined

-- Evalua un comando en un estado dado
evalComm :: Comm -> m ()
evalComm = undefined

-- Evalua una expresion entera, sin efectos laterales
evalIntExp :: IntExp -> m Int
evalIntExp = undefined

-- Evalua una expresion entera, sin efectos laterales
evalBoolExp :: BoolExp -> m Bool
evalBoolExp = undefined
