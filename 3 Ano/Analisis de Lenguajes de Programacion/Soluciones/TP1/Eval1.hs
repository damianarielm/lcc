module Eval1 (eval) where

import AST

-- Estados
type State = [(Variable,Integer)]

-- Estado nulo
initState :: State
initState = []

-- Busca el valor de una variabl en un estado
-- Completar la definicion
lookfor :: Variable -> State -> Integer
lookfor v ((a,b):xs) | v == a    = b
                     | otherwise = lookfor v xs

-- Cambia el valor de una variable en un estado
-- Completar la definicion
update :: Variable -> Integer -> State -> State
update v i s = (v,i) : filter ((v /=) . fst) s

-- Evalua un programa en el estado nulo
eval :: Comm -> State
eval p = evalComm p initState

-- Evalua un comando en un estado dado
-- Completar definicion
evalComm :: Comm -> State -> State
evalComm Skip s           = s
evalComm (Let v e) s      = update v (evalIntExp e s) s
evalComm (Seq c0 c1) s    = evalComm c1 $ evalComm c0 s
evalComm (Cond b c0 c1) s = if evalBoolExp b s
                            then evalComm c0 s
                            else evalComm c1 s
evalComm (Repeat c0 b) s  = evalComm (Cond b Skip (Repeat c0 b)) $ evalComm c0 s

-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalIntExp :: IntExp -> State -> Integer
evalIntExp (Const i) _     = i
evalIntExp (Var v) s       = lookfor v s
evalIntExp (UMinus e) s    = negate $ evalIntExp e s
evalIntExp (Plus e0 e1) s  = evalIntExp e0 s + evalIntExp e1 s
evalIntExp (Minus e0 e1) s = evalIntExp e0 s - evalIntExp e1 s
evalIntExp (Times e0 e1) s = evalIntExp e0 s * evalIntExp e1 s
evalIntExp (Div e0 e1) s   = evalIntExp e0 s `div` evalIntExp e1 s

-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalBoolExp :: BoolExp -> State -> Bool
evalBoolExp BTrue _       = True
evalBoolExp BFalse _      = False
evalBoolExp (Eq e1 e2) s  = evalIntExp e1 s  == evalIntExp e2 s
evalBoolExp (Lt e1 e2) s  = evalIntExp e1 s  <  evalIntExp e2 s
evalBoolExp (Gt e1 e2) s  = evalIntExp e1 s  >  evalIntExp e1 s
evalBoolExp (And b1 b2) s = evalBoolExp b1 s && evalBoolExp b2 s
evalBoolExp (Or b1 b2) s  = evalBoolExp b2 s || evalBoolExp b2 s
evalBoolExp (Not b) s     = not $ evalBoolExp b s
