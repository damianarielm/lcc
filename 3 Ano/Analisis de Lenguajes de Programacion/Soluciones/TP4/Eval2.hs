module Eval2 (eval) where

import AST
import Control.Applicative (Applicative(..))
import Control.Monad       (liftM, liftM2, ap)
import Data.Maybe

-- Estados
type Env = [(Variable,Int)]

-- Estado nulo
initState :: Env
initState = []

-- Mónada estado
newtype StateError a = StateError { runStateError :: Env -> Maybe (a, Env) }

-- Clase para representar mónadas con estado de variables
class Monad m => MonadState m where
    -- Busca el valor de una variable
    lookfor :: Variable -> m Int
    -- Cambia el valor de una variable
    update :: Variable -> Int -> m ()

-- Para calmar al GHC
instance Functor StateError where
    fmap = liftM

instance Applicative StateError where
    pure   = return
    (<*>)  = ap

-- Clase para representar mónadas que lanzan errores
class Monad m => MonadError m where
    -- Lanza un error
    throw :: m a

instance Monad StateError where
    return x = StateError (\s -> Just (x, s))
    m >>= f  = StateError (\s -> (runStateError m) s >>= \(x, s') ->
                                 (runStateError (f x) s'))

instance MonadError StateError where
    throw = StateError (\_ -> Nothing)

instance MonadState StateError where
    lookfor v  = StateError (\s -> lookup v s >>= \x -> Just (x, s))
    update v i = StateError (\s -> Just ((), replace s))
                 where replace vs = (v, i) : (filter ((/= v) . fst) vs)


-- Evalua un programa en el estado nulo
eval :: Comm -> Env
eval c = case runStateError (evalComm c) initState of
         Nothing -> []
         Just (_, s) -> s

-- Evalua un comando en un estado dado
evalComm :: (MonadState m, MonadError m) => Comm -> m ()
evalComm Skip           = return ()
evalComm (Let v e)      = evalIntExp e >>= update v
evalComm (Seq c1 c2)    = evalComm c1 >> evalComm c2
evalComm (Cond b c1 c2) = evalBoolExp b >>= \b ->
                          if b then evalComm c1 else evalComm c2
evalComm (While b c)    = evalComm (Cond b (Seq c (While b c)) Skip)

-- Evalua una expresion entera, sin efectos laterales
evalIntExp :: (MonadState m, MonadError m) => IntExp -> m Int
evalIntExp (Const i)     = return i
evalIntExp (Var v)       = lookfor v
evalIntExp (UMinus e)    = evalIntExp e >>= return . negate
evalIntExp (Plus e1 e2)  = (liftM2 (+)) (evalIntExp e1) (evalIntExp e2)
evalIntExp (Minus e1 e2) = (liftM2 (-)) (evalIntExp e1) (evalIntExp e2)
evalIntExp (Times e1 e2) = (liftM2 (*)) (evalIntExp e1) (evalIntExp e2)
evalIntExp (Div e1 e2)   = evalIntExp e2 >>= \e2' ->
                           if e2' == 0 then throw
                           else (liftM2 div) (evalIntExp e1) (evalIntExp e2)

-- Evalua una expresion entera, sin efectos laterales
evalBoolExp :: (MonadState m, MonadError m) => BoolExp -> m Bool
evalBoolExp BTrue       = return True
evalBoolExp BFalse      = return False
evalBoolExp (Eq e1 e2)  = (liftM2 (==)) (evalIntExp e1) (evalIntExp e2)
evalBoolExp (Lt e1 e2)  = (liftM2 (<)) (evalIntExp e1) (evalIntExp e2)
evalBoolExp (Gt e1 e2)  = (liftM2 (>)) (evalIntExp e1) (evalIntExp e2)
evalBoolExp (And e1 e2) = (liftM2 (&&)) (evalBoolExp e1) (evalBoolExp e2)
evalBoolExp (Or e1 e2)  = (liftM2 (||)) (evalBoolExp e1) (evalBoolExp e2)
evalBoolExp (Not e)     = (liftM not) (evalBoolExp e)
