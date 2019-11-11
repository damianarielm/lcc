module Eval3 (eval) where

import AST
import Control.Applicative (Applicative(..))
import Control.Monad       (liftM, liftM2, ap)

-- Estados
type Env = [(Variable,Int)]

-- Estado nulo
initState :: Env
initState = []

newtype StateErrorT a = StateErrorT { runStateErrorT :: Env -> Maybe (a, Env, Int) }

class Monad m => MonadError m where
    throw :: m a

class Monad m => MonadState m where
    lookfor :: Variable -> m Int
    update :: Variable -> Int -> m ()

class Monad m => MonadTick m where
    tick :: m ()

instance Functor StateErrorT where
    fmap = liftM

instance Applicative StateErrorT where
    pure = return
    (<*>) = ap

instance Monad StateErrorT where
    return x = StateErrorT (\s -> Just (x, s, 0))
    m >>= f  = StateErrorT (\s -> runStateErrorT m s >>= \(x, s', n) ->
                                  runStateErrorT (f x) s' >>= \(a, b, c) ->
                                  Just (a, b, c + n))

instance MonadState StateErrorT where
    lookfor v  = StateErrorT (\s -> lookup v s >>= \x -> Just (x, s, 0))
    update v i = StateErrorT (\s -> Just ((), replace s, 0))
                 where replace vs = (v, i) : (filter ((/= v) . fst) vs)

instance MonadTick StateErrorT where
    tick = StateErrorT (\s -> Just ((), s, 1))

instance MonadError StateErrorT where
    throw = StateErrorT (\s -> Nothing)

-- Evalua un programa en el estado nulo
eval :: Comm -> (Env, Int)
eval c = case runStateErrorT (evalComm c) initState of
         Nothing -> ([], 0)
         Just (_, s, i) -> (s, i)

-- Evalua un comando en un estado dado
evalComm :: (MonadState m, MonadError m, MonadTick m) => Comm -> m ()
evalComm Skip           = return ()
evalComm (Let v e)      = evalIntExp e >>= update v
evalComm (Seq c1 c2)    = evalComm c1 >> evalComm c2
evalComm (Cond b c1 c2) = evalBoolExp b >>= \b ->
                          if b then evalComm c1 else evalComm c2
evalComm (While b c)    = evalComm (Cond b (Seq c (While b c)) Skip)

-- Evalua una expresion entera, sin efectos laterales
evalIntExp :: (MonadState m, MonadError m, MonadTick m) => IntExp -> m Int
evalIntExp (Const i)     = return i
evalIntExp (Var v)       = lookfor v
evalIntExp (UMinus e)    = evalIntExp e >>= return . negate
evalIntExp (Plus e1 e2)  = tick >> (liftM2 (+)) (evalIntExp e1) (evalIntExp e2)
evalIntExp (Minus e1 e2) = tick >> (liftM2 (-)) (evalIntExp e1) (evalIntExp e2)
evalIntExp (Times e1 e2) = tick >> (liftM2 (*)) (evalIntExp e1) (evalIntExp e2)
evalIntExp (Div e1 e2)   = evalIntExp e2 >>= \e2' ->
                           if e2' == 0 then throw
                           else tick >> (liftM2 div) (evalIntExp e1) (evalIntExp e2)

-- Evalua una expresion entera, sin efectos laterales
evalBoolExp :: (MonadState m, MonadError m, MonadTick m) => BoolExp -> m Bool
evalBoolExp BTrue       = return True
evalBoolExp BFalse      = return False
evalBoolExp (Eq e1 e2)  = (liftM2 (==)) (evalIntExp e1) (evalIntExp e2)
evalBoolExp (Lt e1 e2)  = (liftM2 (<)) (evalIntExp e1) (evalIntExp e2)
evalBoolExp (Gt e1 e2)  = (liftM2 (>)) (evalIntExp e1) (evalIntExp e2)
evalBoolExp (And e1 e2) = (liftM2 (&&)) (evalBoolExp e1) (evalBoolExp e2)
evalBoolExp (Or e1 e2)  = (liftM2 (||)) (evalBoolExp e1) (evalBoolExp e2)
evalBoolExp (Not e)     = (liftM not) (evalBoolExp e)
