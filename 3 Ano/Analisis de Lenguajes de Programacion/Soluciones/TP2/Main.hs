{-# OPTIONS -XRecordWildCards #-}

module Main where

  import System.Console.Readline
  import System.IO
  import System.Environment
  import Control.Exception (catch,IOException)

  import Control.Monad.Except
-- En versiones viejas de GHC reemplazar este import por 
--  import Control.Monad.Error

  import Data.List
  import Data.Char
  import Text.PrettyPrint.HughesPJ (render)
  import Text.ParserCombinators.Parsec (many,Parser,parse)

  import Common
  import PrettyPrinter
  import Untyped
  import Parser

---------------------
--- Interpreter
---------------------

  main :: IO ()
  main = do args <- getArgs
            readevalprint args (S True "" [])

  ioExceptionCatcher :: IOException -> IO (Maybe a)
  ioExceptionCatcher _ = return Nothing

  iname , iprompt :: String
  iname = "cálculo lambda no tipado"
  iprompt = "UT> "


  data State = S { inter :: Bool,       -- True, si estamos en modo interactivo.
                   lfile :: String,     -- Ultimo archivo cargado (para hacer "reload")
                   ve :: NameEnv Term  -- Entorno con variables globales y su valor
                 }

  --  read-eval-print loop
  readevalprint :: [String] -> State -> IO ()
  readevalprint args state@(S {..}) =
    let rec st =
          do
            mx <- catch
                   (if inter
                    then readline iprompt 
                    else fmap Just getLine)
                    ioExceptionCatcher
            case mx of
              Nothing   ->  return ()
              Just ""   ->  rec st
              Just x    ->
                do
                  when inter (addHistory x)
                  c  <- interpretCommand x
                  st' <- handleCommand st c
                  maybe (return ()) rec st'
    in
      do
--        state' <- compileFile (state {lfile=prelude, inter=False}) prelude
        state' <- compileFiles (prelude:args) state 
        when inter $ putStrLn ("Intérprete de " ++ iname ++ ".\n" ++
                               "Escriba :? para recibir ayuda.")
        --  enter loop
        rec state' {inter=True}

  data Command = Compile CompileForm
               | Print String
               | Recompile  
               | Browse
               | Quit
               | Help
               | Noop

  data CompileForm = CompileInteractive  String
                   | CompileFile         String
  
  interpretCommand :: String -> IO Command
  interpretCommand x
    =  if isPrefixOf ":" x then
         do  let  (cmd,t')  =  break isSpace x
                  t         =  dropWhile isSpace t'
             --  find matching commands
             let  matching  =  filter (\ (Cmd cs _ _ _) -> any (isPrefixOf cmd) cs) commands
             case matching of
               []  ->  do  putStrLn ("Comando desconocido `" ++ cmd ++ "'. Escriba :? para recibir ayuda.")
                           return Noop
               [Cmd _ _ f _]
                   ->  do  return (f t)
               _   ->  do  putStrLn ("Comando ambigüo, podría ser " ++ 
                                     concat (intersperse ", " [ head cs | Cmd cs _ _ _ <- matching ]) ++ ".")
                           return Noop

       else
         return (Compile (CompileInteractive x))

  handleCommand :: State -> Command -> IO (Maybe State)
  handleCommand state@(S {..}) cmd
    =  case cmd of
         Quit   ->  when (not inter) (putStrLn "!@#$^&*") >> return Nothing
         Noop   ->  return (Just state)
         Help   ->  putStr (helpTxt commands) >> return (Just state)
         Browse ->  do  putStr (unlines [ s | s <- reverse (nub (map fst ve)) ])
                        return (Just state)
         Compile c ->
                    do  state' <- case c of
                                   CompileInteractive s -> compilePhrase state s
                                   CompileFile f        -> compileFile (state {lfile=f}) f
                        return (Just state')
         Print s   -> printPhrase s >> return (Just state)
         Recompile -> if null lfile 
                        then putStrLn "No hay un archivo cargado.\n" 
                             >> return (Just state) 
                        else handleCommand state (Compile (CompileFile lfile))

  data InteractiveCommand = Cmd [String] String (String -> Command) String

  commands :: [InteractiveCommand]
  commands
    =  [ Cmd [":browse"]      ""        (const Browse) "Ver los nombres en scope",
         Cmd [":load"]        "<file>"  (Compile . CompileFile)
                                                       "Cargar un programa desde un archivo",
         Cmd [":print"]       "<exp>"   Print          "Imprime un término y sus ASTs sin evaluarlo",
         Cmd [":reload"]      "<file>"  (const Recompile) "Volver a cargar el último archivo",
         Cmd [":quit"]        ""        (const Quit)   "Salir del intérprete",
         Cmd [":help",":?"]   ""        (const Help)   "Mostrar esta lista de comandos" ]
  
  helpTxt :: [InteractiveCommand] -> String
  helpTxt cs
    =  "Lista de comandos:  Cualquier comando puede ser abreviado a :c donde\n" ++
       "c es el primer caracter del nombre completo.\n\n" ++
       "<expr>                  evaluar la expresión\n" ++
       "def <var> = <expr>      definir una variable\n" ++
       unlines (map (\ (Cmd c a _ d) -> 
                     let  ct = concat (intersperse ", " (map (++ if null a then "" else " " ++ a) c))
                     in   ct ++ replicate ((24 - length ct) `max` 2) ' ' ++ d) cs)

  compileFiles :: [String] -> State -> IO State
  compileFiles [] s      = return s
  compileFiles (x:xs) s  = do s' <- compileFile (s {lfile=x, inter=False})  x
                              compileFiles xs s'

  compileFile :: State -> String -> IO State
  compileFile state@(S {..}) f =
    do
      putStrLn ("Abriendo "++f++"...")
      let f'= reverse(dropWhile isSpace (reverse f))
      x <- catch (readFile f')
                 (\e -> do let err = show (e :: IOException)
                           hPutStr stderr ("No se pudo abrir el archivo " ++ f' ++ ": " ++ err ++"\n")
                           return "")
      stmts <- parseIO f' (many parseTermStmt) x
      maybe (return state) (foldM handleStmt state) stmts


  compilePhrase :: State -> String -> IO State
  compilePhrase state x =
    do
      x' <- parseIO "<interactive>" parseTermStmt x
      maybe (return state) (handleStmt state) x'

  printPhrase   :: String -> IO ()
  printPhrase x =
    do
      x' <- parseIO "<interactive>" (parseStmt p) x
      maybe (return ()) printStmt x'
     where p :: Parser (LamTerm,Term)
           p = do a <- parseLamTerm
                  return (a,conversion a)

  printStmt ::  Stmt (LamTerm,Term) -> IO ()
  printStmt stmt =  
    do
      let outtext = case stmt of
                       Def x (_,e)  -> "def "++x++" = "++render (printTerm e)
                       Eval (d,e)   -> "LamTerm AST:\n"++
                                       show d++
                                       "\n\nTerm AST:\n"++
                                       show e++
                                       "\n\nSe muestra como:\n"++
                                       render (printTerm e)
      putStrLn outtext

  parseIO :: String -> Parser a -> String -> IO (Maybe a)
  parseIO f p x = case parse (totParser p) f x of
                    Left e  -> putStrLn (show e) >> return Nothing
                    Right r -> return (Just r)

  handleStmt ::  State -> Stmt Term -> IO State
  handleStmt state stmt =
    do
      case stmt of
          Def x e    -> checkEval x e
          Eval e     -> checkEval it e
    where
      checkEval i t = do
         let v = {- evalK -} eval (ve state) t
         _ <- when (inter state) $ do
                  let outtext = if i == it then render (printTerm v)
                                           else i
                  putStrLn outtext
         return (state { ve = (i, v) : ve state})

  prelude :: String
  prelude = "Prelude.lam"

  it :: String
  it = "it"
