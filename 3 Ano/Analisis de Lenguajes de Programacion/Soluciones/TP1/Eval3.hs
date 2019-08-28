module Eval3 (eval) where

import AST
import Control.Monad

-- Estados
type State = [(Variable,Integer)]
type Trace = [State]

data Error = DivByZero | UndefVar deriving (Eq, Show)

-- Estado nulo
initState :: State
initState = []

initTrace :: Trace
initTrace = [[]]

-- Busca el valor de una variabl en un estado
-- Completar la definicion
lookfor :: Variable -> State -> Either Error Integer
lookfor _ [] = Left UndefVar
lookfor v ((a,b):xs) | v == a    = Right b
                     | otherwise = lookfor v xs

-- Cambia el valor de una variable en un estado
-- Completar la definicion
update :: Variable -> Integer -> (State, Trace) -> (State, Trace)
update v i (s,t) = let s' = (v,i) : filter ((v /=) . fst) s
                       t' = t ++ [s']
                   in  (s', t')

-- Evalua un programa en el estado nulo
eval :: Comm -> Either Error (State, Trace)
eval p = evalComm p (initState, initTrace)

-- Evalua un comando en un estado dado
-- Completar definicion
evalComm :: Comm -> (State, Trace) -> Either Error (State, Trace)
evalComm Skip (s,t)           = return (s,t)
evalComm (Let v e) (s,t)      = liftM (flip (update v) (s,t)) (evalIntExp e s)
evalComm (Seq c0 c1) (s,t)    = evalComm c0 (s,t) >>= evalComm c1
evalComm (Cond b c0 c1) (s,t) = evalBoolExp b s >>= \b -> if b then evalComm c0 (s,t)
                                                               else evalComm c1 (s,t)
evalComm (Repeat c0 b) (s,t)  = evalComm c0 (s,t) >>= evalComm (Cond b Skip (Repeat c0 b))
evalComm (While b c) (s,t)    = evalComm (Cond b (Seq c (While b c)) Skip) (s,t)

-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalIntExp :: IntExp -> State -> Either Error Integer
evalIntExp (Const i) _     = Right i
evalIntExp (Var v) s       = lookfor v s
evalIntExp (UMinus e) s    = evalIntExp e s >>= return . negate
evalIntExp (Plus e0 e1) s  = (liftM2 (+)) (evalIntExp e0 s) (evalIntExp e1 s)
evalIntExp (Minus e0 e1) s = (liftM2 (-)) (evalIntExp e0 s) (evalIntExp e1 s)
evalIntExp (Times e0 e1) s = (liftM2 (*)) (evalIntExp e0 s) (evalIntExp e1 s)
evalIntExp (Div e0 e1) s   = do e0' <- evalIntExp e0 s
                                e1' <- evalIntExp e1 s
                                if e1' == 0 then Left DivByZero else return $ div e0' e1'

-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalBoolExp :: BoolExp -> State -> Either Error Bool
evalBoolExp BTrue _       = return True
evalBoolExp BFalse _      = return False
evalBoolExp (Eq e1 e2) s  = (liftM2 (==)) (evalIntExp e1 s)  (evalIntExp e2 s)
evalBoolExp (Lt e1 e2) s  = (liftM2 (<))  (evalIntExp e1 s)  (evalIntExp e2 s)
evalBoolExp (Gt e1 e2) s  = (liftM2 (>))  (evalIntExp e1 s)  (evalIntExp e2 s)
evalBoolExp (And b1 b2) s = (liftM2 (&&)) (evalBoolExp b1 s) (evalBoolExp b2 s)
evalBoolExp (Or b1 b2) s  = (liftM2 (||)) (evalBoolExp b1 s) (evalBoolExp b2 s)
evalBoolExp (Not b) s     = liftM not $ evalBoolExp b s
