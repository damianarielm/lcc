{-# OPTIONS -XRecordWildCards #-}
module Main where

  import Control.Exception (catch,IOException)
  import Control.Monad.Except
--  import Control.Monad.Error
  import Data.Char
  import Data.List
  import Data.Maybe
  import Prelude hiding (print)
  import System.Console.Readline
  import System.Environment
  import System.IO hiding (print)
  import Text.PrettyPrint.HughesPJ (render,text)

  import Common
  import PrettyPrinter
  import Simplytyped
  import Parse
---------------------
--- Interpreter
---------------------

  main :: IO ()
  main = do args <- getArgs
            readevalprint args (S True "" [])

  ioExceptionCatcher :: IOException -> IO (Maybe a)
  ioExceptionCatcher _ = return Nothing

  iname, iprompt :: String
  iname = "cálculo lambda simplemente tipado"
  iprompt = "ST> "


  data State = S { inter :: Bool,       -- True, si estamos en modo interactivo.
                   lfile :: String,     -- Ultimo archivo cargado (para hacer "reload")
                   ve :: NameEnv Value Type  -- Entorno con variables globales y su valor  [(Name, (Value, Type))]
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
                  c   <- interpretCommand x
                  st' <- handleCommand st c
                  maybe (return ()) rec st'
    in
      do
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
               | FindType String

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
               []  ->  do  putStrLn ("Comando desconocido `" ++ 
                                     cmd                     ++ 
                                     "'. Escriba :? para recibir ayuda.")
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
         Quit       ->  when (not inter) (putStrLn "!@#$^&*") >> return Nothing
         Noop       ->  return (Just state)
         Help       ->  putStr (helpTxt commands) >> return (Just state)
         Browse     ->  do  putStr (unlines [ s | Global s <- reverse (nub (map fst ve)) ])
                            return (Just state)
         Compile c  ->  do  state' <- case c of
                                   CompileInteractive s -> compilePhrase state s
                                   CompileFile f        -> compileFile (state {lfile=f}) f
                            return (Just state')
         Print s    ->  let s' = reverse (dropWhile isSpace (reverse (dropWhile isSpace s)))
                        in printPhrase s' >> return (Just state)
         Recompile  -> if null lfile
                        then putStrLn "No hay un archivo cargado.\n" >>
                             return (Just state) 
                        else handleCommand state (Compile (CompileFile lfile))
         FindType s -> do x' <- parseIO "<interactive>" term_parse s
                          t  <- case x' of
                                 Nothing -> return $ Left "Error en el parsing."
                                 Just x -> return $ infer ve $ conversion $ x
                          case t of
                            Left err -> putStrLn ("Error de tipos: " ++ err) >>
                                        return ()
                            Right t' -> putStrLn $ render $ printType t'
                          return (Just state)

  data InteractiveCommand = Cmd [String] String (String -> Command) String

  commands :: [InteractiveCommand]
  commands
    =  [ Cmd [":browse"]      ""        (const Browse) "Ver los nombres en scope",
         Cmd [":load"]        "<file>"  (Compile . CompileFile)
                                                       "Cargar un programa desde un archivo",
         Cmd [":print"]       "<exp>"   Print          "Imprime un término y sus ASTs",
         Cmd [":reload"]      "<file>"  (const Recompile) "Volver a cargar el último archivo",
         Cmd [":quit"]        ""        (const Quit)   "Salir del intérprete",
         Cmd [":help",":?"]   ""        (const Help)   "Mostrar esta lista de comandos",
         Cmd [":type"]        "<term>"  (FindType) "Inferir el tipo de un término" ]

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
  compileFile state@(S {..}) f = do
      putStrLn ("Abriendo "++f++"...")
      let f'= reverse(dropWhile isSpace (reverse f))
      x     <- catch (readFile f')
                 (\e -> do let err = show (e :: IOException)
                           hPutStr stderr ("No se pudo abrir el archivo " ++ f' ++ ": " ++ err ++"\n")
                           return "")
      stmts <- parseIO f' (stmts_parse) x
      maybe (return state) (foldM handleStmt state) stmts

  compilePhrase :: State -> String -> IO State
  compilePhrase state x =
    do
      x' <- parseIO "<interactive>" stmt_parse x
      maybe (return state) (handleStmt state) x'

  printPhrase   :: String -> IO ()
  printPhrase x =
    do
      x' <- parseIO "<interactive>" stmt_parse x
      maybe (return ()) (printStmt . fmap (\y -> (y, conversion y)) ) x'

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

  parseIO :: String -> (String -> ParseResult a) -> String -> IO (Maybe a)
  parseIO f p x = case p x of
                       Failed e  -> do putStrLn (f++": "++e)
                                       return Nothing
                       Ok r      -> return (Just r)

  handleStmt :: State -> Stmt LamTerm -> IO State
  handleStmt state stmt =
    do
      case stmt of
          Def x e    -> checkType x (conversion e)
          Eval e     -> checkType it (conversion e)
    where
      checkType i t = do
        case infer (ve state) t of
          Left err -> putStrLn ("Error de tipos: " ++ err) >> return state
          Right ty -> checkEval i t ty
      checkEval i t ty = do
         let v = eval (ve state) t
         _ <- when (inter state) $ do
                  let outtext = if i == it then render (printTerm (quote v))
                                           else render (text i)
                  putStrLn outtext
         return (state { ve = (Global i, (v, ty)) : ve state})

  prelude :: String
  prelude = "Prelude.lam"

  it :: String
  it = "it"
