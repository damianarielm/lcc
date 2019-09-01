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
shift (Lam t) c d    = Lam $ shift t (c + 1) d
shift (t :@: t') c d = shift t c d :@: shift t' c d
shift (Bound k) c d  = if k < c then Bound k else Bound $ k + d
shift t _ _          = t


subst :: Term -> Term -> Int -> Term
subst (Bound k) t' i   = if k == i then t' else Bound k
subst (Lam t1) t' i    = Lam $ subst t1 (shift t' 0 1) (i + 1)
subst (t1 :@: t2) t' i = subst t1 t' i :@: subst t2 t' i
subst t _ _            = t


breduce (Lam t :@: v) = shift (subst t (shift v 0 1) 0) 0 (-1)


eval :: NameEnv Term -> Term -> Term
eval xs (Free x)        = maybe (Free x) id (lookup x xs)
eval xs (Bound i)       = Bound i
eval xs (Lam t)         = Lam $ eval xs t
eval xs (Lam t1 :@: t2) = eval xs $ breduce $ Lam t1 :@: t2
eval xs (t1 :@: t2)     = case eval xs t1 of
                          Lam t -> eval xs $ Lam t :@: t2
                          t     -> t :@: eval xs t2
