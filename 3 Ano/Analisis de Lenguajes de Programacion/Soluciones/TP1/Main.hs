module Main where

import System.Environment (getArgs)
import Parser (parseComm)

-- Modificar este import para usar diferentes evaluadores
import Eval3
---------------------------------------------------------

main :: IO ()
main = do arg:_ <- getArgs
          run arg

-- Ejecuta un programa a partir de su archivo fuente
run :: [Char] -> IO ()
run ifile =
    do
    s <- readFile ifile
    case parseComm ifile s of
      Left error -> print error
      Right t    -> print (eval t) --imprimir el resultado de evaluar.
      -- Right t    -> print t        --imprimir sin evaluar (para testear Parser)
