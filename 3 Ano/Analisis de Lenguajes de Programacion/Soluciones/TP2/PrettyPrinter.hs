
module PrettyPrinter (printTerm) where

  import Prelude hiding ((<>))
  import Common
  import Text.PrettyPrint.HughesPJ

  -- lista de posibles nombres para variables
  vars :: [String]
  vars = [ c : n | n <- "" : map show [1..], c <- ['x','y','z'] ++ ['a'..'w'] ]

  parensIf :: Bool -> Doc -> Doc
  parensIf True  = parens
  parensIf False = id

  pp :: Int -> [String] -> Term -> Doc
  pp ii vs (Bound k)           = text (vs !! (ii - k - 1))
  pp _  vs (Free s)            =  text s
  pp ii vs (i :@: c)           =  sep [parensIf (isLam i) (pp ii vs i), 
                                       nest 1 (parensIf (isLam c || isApp c) (pp ii vs c))]
                                    -- el chequeo por isLam no es necesario pero queda bien
  pp ii vs (Lam c)             =  text "\\" <>
                                  text (vs !! ii) <>
                                  plambda (ii+1) vs c

  plambda ii vs (Lam c)        =  text " " <>
                                  text (vs !! ii) <>
                                  plambda (ii+1) vs c
  plambda ii vs c              =  text ". " <>
                                  pp ii vs c

  isLam (Lam _) = True
  isLam  _      = False

  isApp (_ :@: _) = True
  isApp _         = False

  fv :: Term -> [String]
  fv (Bound _)           = []
  fv (Free n)            = [n]
  fv (t :@: u)           = fv t ++ fv u
  fv (Lam c)             = fv c

  printTerm  :: Term -> Doc
  printTerm t = pp 0 (filter (\v -> not $ elem v (fv t)) vars) t
