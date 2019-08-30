module Untyped where

import Control.Monad
import Data.List

import Common


----------------------------------------------
-- Seccón 2 - Representación de Términos Lambda 
-- Ejercicio 2: Conversión de Términos
----------------------------------------------

conversion  :: LamTerm -> Term
conversion lt = conver' [] lt where
                conver' xs (Abs x y) = Lam $ conver' (x:xs) y
                conver' xs (App x y) = conver' xs x :@: conver' xs y
                conver' xs (LVar x)  = maybe (Free x) Bound $ elemIndex x xs

-------------------------------
-- Sección 3 - Evaluación
-------------------------------

shift :: Term -> Int -> Int -> Term
shift = undefined


subst :: Term -> Term -> Int -> Term
subst = undefined


eval :: NameEnv Term -> Term -> Term
eval = undefined
