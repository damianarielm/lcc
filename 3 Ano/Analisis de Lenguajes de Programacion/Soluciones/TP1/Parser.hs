module Parser where

import Text.ParserCombinators.Parsec
import Text.Parsec.Token
import Text.Parsec.Language (emptyDef)
import AST

-----------------------
-- Funcion para facilitar el testing del parser.
totParser :: Parser a -> Parser a
totParser p = do
                  whiteSpace lis
                  t <- p
                  eof
                  return t

-- Analizador de Tokens
lis :: TokenParser u
lis = makeTokenParser (emptyDef   { commentStart  = "/*"
                                  , commentEnd    = "*/"
                                  , commentLine   = "//"
                                  , opLetter      = char '='
                                  , reservedNames = ["true","false","skip","if",
                                                     "then","else","end", "while",
                                                     "do", "repeat", "until"]
                                  })

----------------------------------
--- Parser de expressiones enteras
-----------------------------------

intexp :: Parser IntExp
intexp  = chainl1 term plusminus

nat = do n <- integer lis
         return $ Const n

var = do v <- identifier lis
         return $ Var v

intnegation = do reservedOp lis "-"
                 n <- intexp
                 return $ UMinus n

plusminus = do reservedOp lis "+"
               return Plus
            <|> do reservedOp lis "-"
                   return Minus

timesdiv = do reservedOp lis "*"
              return Times
           <|> do reservedOp lis "/"
                  return Div

term = chainl1 (intnegation <|> nat <|> var <|> parens lis intexp) timesdiv


-----------------------------------
--- Parser de expressiones booleanas
------------------------------------

boolexp :: Parser BoolExp
boolexp = chainl1 conjunction orOp

conjunction = chainl1 (boolnegation <|> boolean <|> comparsion <|> parens lis boolexp) andOp

boolnegation = do reservedOp lis "~"
                  b <- boolexp
                  return $ Not b

boolean = do reserved lis "true"
             return BTrue
             <|> do reserved lis "false"
                    return BFalse

comparsion = do e1 <- intexp
                op <- compareOp
                e2 <- intexp
                return $ op e1 e2

compareOp = do reservedOp lis "="
               return Eq
               <|> do reservedOp lis ">"
                      return Gt
                      <|> do reservedOp lis "<"
                             return Lt

orOp = do reservedOp lis "|"
          return Or

andOp = do reservedOp lis "&"
           return And

-----------------------------------
--- Parser de comandos
-----------------------------------

comm :: Parser Comm
comm = chainl1 (assignment <|> ifthenelse <|> repeatuntil <|> skip) semicolon

skip = do reserved lis "skip"
          return Skip

assignment = do var <- identifier lis
                reservedOp lis ":="
                e <- intexp
                return $ Let var e

semicolon = do reservedOp lis ";"
               return Seq

ifthenelse = do reserved lis "if"
                b <- boolexp
                reserved lis "then"
                c1 <- comm
                reserved lis "else"
                c2 <- comm
                reserved lis "end"
                return $ Cond b c1 c2

repeatuntil = do reserved lis "repeat"
                 c <- comm
                 reserved lis "until"
                 b <- boolexp
                 reserved lis "end"
                 return $ Repeat c b

------------------------------------
-- Función de parseo
------------------------------------
parseComm :: SourceName -> String -> Either ParseError Comm
parseComm = parse (totParser comm)
