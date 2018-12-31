-- happy Parser.y & ghci Main.hs -XRankNTypes
-- runhaskell --ghc-arg=-XRankNTypes Main.hs examples/langton/langton.atm examples/langton/langton.ini

module Main where

import Types
import Matrix
import Rules
import Parser (lexer, parse)
import System.Environment (getArgs)
import UI.NCurses -- apt install c2hs & cabal install ncurses 

main :: IO ()
main = do definition : initial : rest <- getArgs
          a <- readFile definition
          s <- readFile initial
          let (states, rules) = parse $ lexer a
              frontier = if null rest then Wrap else read $ rest !! 0 -- Tipo de frontera
              start = if (length rest) < 2 then 0 else read $ rest !! 1 -- Generacion inicial
              frames = if (length rest) < 3 then 0 else read $ rest !! 2 -- Cantidad de generaciones
              skip = if (length rest) < 4 then 1 else read $ rest !! 3 -- Salto de frames
              time = if (length rest) < 5 then 0 else read $ rest !! 4 -- Pausa entre frames
              m = fromString s -- Divide por salto de linea y rellana espacios
              r = toInteger $ rows m + 3 -- Filas extra para el borde y generacion
              c = toInteger $ cols m + 2 -- Columnas extra para el borde
              animation = if frames == 0 then x else take frames x
                          where x = drop start $ iterate (step $ makeTransition frontier rules) m
          runCurses $ do
            colors <- sequence [newColorID c1 c2 i | ((_, _, c1, c2), i) <- zip states [1..]]
            setCursorMode CursorInvisible
            w <- newWindow r c 0 0
            play animation w start (zipWith (\(c1,c2,_,_) c -> (c1,c2,c)) states colors) (toInteger time) skip

play :: Animation -> Window -> Int -> ColorTable -> Integer -> Int -> Curses ()
play []     w g _ s x = do updateWindow w $ do
                             moveCursor 1 1
                             drawString $ "Generacion: " ++ show g ++ ". Fin de la simulacion."
                           render
                           getEvent w Nothing
                           return ()
play (f:fs) w g t s x = do updateWindow w $ do
                             drawBorder Nothing Nothing Nothing Nothing Nothing Nothing Nothing Nothing
                             moveCursor 1 1
                             drawString $ "Generacion: " ++ show g
                             frame 2 f t
                           render
                           e <- getEvent w (Just 0)
                           case e of
                             (Just (EventCharacter ' ')) -> do { getEvent w Nothing; play (drop x fs) w (g+x) t s x }
                             _ -> do { getEvent w (Just s); play (drop x fs) w (g+x) t s x }

frame :: Integer -> Matrix -> ColorTable -> Update ()
frame _ []         _ = do moveCursor 0 0
frame r (row:rest) t = do moveCursor r 1
                          mapM_ drawGlyph [ paint c t | c <- row ]
                          frame (r+1) rest t

paint :: Char -> ColorTable -> Glyph
paint c l = let l' = filter ((==c) . fst') l
            in case l' of
               [] -> Glyph c []
               (_, c', color):ls -> Glyph c' [ AttributeColor color ]
            where fst' (x,_,_) = x
