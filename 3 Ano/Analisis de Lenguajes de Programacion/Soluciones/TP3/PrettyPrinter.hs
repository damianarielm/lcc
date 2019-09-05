module PrettyPrinter (
       printTerm,     -- pretty printer para terminos
       printType,     -- pretty printer para tipos
       )
       where

import Prelude hiding ((<>))
import Common
import Text.PrettyPrint.HughesPJ

-- lista de posibles nombres para variables
vars :: [String]
vars = [ c : n | n <- "" : map show [(1::Integer)..], c <- ['x','y','z'] ++ ['a'..'w'] ]

parensIf :: Bool -> Doc -> Doc
parensIf True  = parens
parensIf False = id

-- pretty-printer de términos

pp :: Int -> [String] -> Term -> Doc
pp ii vs (Bound k)         = text (vs !! (ii - k - 1))
pp _  _  (Free (Global s)) = text s

pp ii vs (i :@: c) = sep [parensIf (isLam i) (pp ii vs i),
                          nest 1 (parensIf (isLam c || isApp c) (pp ii vs c))]
pp ii vs (Lam t c) = text "\\" <>
                     text (vs !! ii) <>
                     text ":" <>
                     printType t <>
                     text ". " <>
                     pp (ii+1) vs c

pp ii vs (Let (Global s) t u) = text ("let " ++ s) <>
                                text " = " <>
                                pp ii vs t <>
                                text " in " <>
                                pp ii vs u

pp ii vs (As s t) = pp ii vs s <> text " as " <> printType t

pp ii vs (Unit) = text "unit"

pp ii vs (Pair s t) = parens $ (pp ii vs s) <> text ", " <> (pp ii vs t)

pp ii vs (Zero) = text "0"

pp ii vs (Suc t) = text "suc " <> pp ii vs t

pp ii vs (Rec s t u) = sep [text "R", parens (pp ii vs s), parens (pp ii vs t), parens (pp ii vs u)]

isLam :: Term -> Bool
isLam (Lam _ _) = True
isLam  _      = False

isApp :: Term -> Bool
isApp (_ :@: _) = True
isApp _         = False

-- pretty-printer de tipos
printType :: Type -> Doc
printType Base         = text "B"
printType (Fun t1 t2)  = sep [ parensIf (isFun t1) (printType t1),
                               text "->",
                               printType t2]
printType UnitT        = text "Unit"
printType (PairT s t)  = text "(" <> printType s <> text ", " <> printType t <> text ")"
printType (NatT)       = text "Nat"

isFun :: Type -> Bool
isFun (Fun _ _)        = True
isFun _                = False

fv :: Term -> [String]
fv (Bound _)         = []
fv (Free (Global n)) = [n]
fv (t :@: u)         = fv t ++ fv u
fv (Lam _ u)         = fv u
fv (Unit)            = []
fv (Zero)            = []
fv (Let n t u)       = fv t ++ fv u
fv (As s t)          = fv s
fv (Pair t u)        = fv t ++ fv u
fv (Fst s)           = fv s
fv (Snd s)           = fv s
fv (Suc s)           = fv s
fv (Rec s t u)       = fv s ++ fv t ++ fv u

---
printTerm :: Term -> Doc 
printTerm t = pp 0 (filter (\v -> not $ elem v (fv t)) vars) t
