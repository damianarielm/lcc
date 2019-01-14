module Main where

import Types
import Matrix
import Rules
import UI.NCurses
import Prelude hiding (drop, null, head, tail)
import Data.Vector as V (drop, null, head, tail, iterateN, toList)
import Parser (lexer, parse)
import System.Environment (getArgs, getProgName)

parseCmd :: [String] -> (String, String, Frontier, Int, Int, Int, Int)
parseCmd (a:i:[]) = (a,i,Wrap,0,10900,0,0)
parseCmd (a:i:f:[]) = (a,i,read f,0,10900,0,0)
parseCmd (a:i:f:s:[]) = (a,i,read f,read s,10900,0,0)
parseCmd (a:i:f:s:e:[]) = (a,i,read f,read s,read e,0,0)
parseCmd (a:i:f:s:e:k:[]) = (a,i,read f,read s,read e,read k,0)
parseCmd (a:i:f:s:e:k:t:_) = (a,i,read f,read s,read e,read k, read t)

readConfig args =
  do let (definition,initial,frontier,start,frames,skip,time) = parseCmd args
     a <- readFile definition
     s <- readFile initial
     let (states, rules) = parse $ lexer a
         m = fromString s
         r = toInteger $ rows m + 3
         c = toInteger $ cols m + 2
         animation = drop start $ iterateN frames (step $ makeTransition frontier (optimize rules)) m
     return (states, r, c, animation, start, toInteger time, skip)

startCurses (states,r,c,animation,start,time,skip) = runCurses $ do
  colors <- sequence [newColorID c1 c2 i | ((_, _, c1, c2), i) <- zip states [1..]]
  setCursorMode CursorInvisible
  setEcho False
  w <- newWindow r c 0 0
  play animation w start (zipWith (\(c1,c2,_,_) c5 -> (c1,c2,c5)) states colors) time skip

main :: IO ()
main = do prog <- getProgName
          args <- getArgs
          if  (length args) < 2
          then do putStrLn $ "Error de sintaxis.\nUso correcto: " ++ prog
                              ++ " AUTOMATA INICIAL [Frontier Start Frames Skip Time]"
          else do config <- readConfig args
                  startCurses config

play :: Animation -> Window -> Int -> ColorTable -> Integer -> Int -> Curses ()
play a w g t s x | null a = do updateWindow w $ do
                                 moveCursor 1 1
                                 drawString $ "Generacion: " ++ show g ++ ". Fin de la simulacion."
                               render
                               getEvent w Nothing
                               return ()
                 | otherwise = let (f,fs) = (head a, tail a)
                               in do updateWindow w $ do
                                       drawBorder Nothing Nothing Nothing Nothing Nothing Nothing Nothing Nothing
                                       moveCursor 1 1
                                       drawString $ "Generacion: " ++ show g
                                       frame 2 f t
                                     render
                                     e <- getEvent w (Just 0)
                                     handleKeys w x fs g t s e

handleKeys :: Window -> Int -> Animation -> Int -> ColorTable -> Integer -> Maybe Event -> Curses ()
handleKeys w x fs g t s e
  | e == (Just (EventCharacter ' ')) = do getEvent w Nothing
                                          play (drop x fs) w (g+x+1) t s x
  | e == (Just (EventSpecialKey KeyRightArrow)) = do updateWindow w $ do
                                                       frame 2 (head fs) t
                                                       moveCursor 1 1
                                                       drawString $ "Generacion: " ++ show (g+1)
                                                     render
                                                     e' <- getEvent w Nothing
                                                     handleKeys w x (drop 1 fs) (g+1) t s e'
  | otherwise = do getEvent w (Just s)
                   play (drop x fs) w (g+x+1) t s x

frame :: Integer -> Matrix -> ColorTable -> Update ()
frame r m t | null m  = do return ()
            | otherwise = let (row, rest) = (head m, tail m)
                          in do moveCursor r 1
                                mapM_ drawGlyph [paint c t | c <- toList row]
                                frame (r+1) rest t

paint :: Char -> ColorTable -> Glyph
paint c l = let l' = filter ((==c) . fst') l
            in case l' of
               [] -> Glyph c []
               (_, c', color):_ -> Glyph c' [AttributeColor color]
            where fst' (x,_,_) = x
