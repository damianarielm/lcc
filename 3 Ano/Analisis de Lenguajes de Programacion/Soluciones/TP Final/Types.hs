module Types where

import Data.Vector (Vector)
import UI.NCurses (Color, ColorID)

type Matrix = Vector (Vector Char)
type Animation = Vector Matrix
type Point  = (Int, Int)
type Neighbours = Point -> Int -> [Point]
type Transition = Point -> Matrix -> Char
type State = (Char, Char, Color, Color)
type ColorTable = [(Char, Char, ColorID)]
type Rule = (Char, [Condition], Char)

data Frontier = Open Char
              | Wrap
              | Reflect
              deriving Read

data Token = TNeighbours | TChebyshev | TManhattan
           | TState      | TBlack     | TRed
           | TGreen      | TYellow    | TBlue
           | TMagenta    | TCyan      | TWhite
           | TColon      | TSemiColon | TApostrophe
           | TPOpen      | TPClose    | TInt Int
           | TChar Char  | TEq        | TNeq
           | TLeq        | TGeq       | TLower
           | TGreater    | TAnd       | TNorth
           | TSouth      | TEast      | TWest
           | TNW         | TNE        | TSW
           | TSE

data Condition = Chebyshev Char Int (Int -> Int -> Bool) Int
               | Manhattan Char Int (Int -> Int -> Bool) Int
               | North Int (Char -> Char -> Bool) Char
               | South Int (Char -> Char -> Bool) Char
               | East Int (Char -> Char -> Bool) Char
               | West Int (Char -> Char -> Bool) Char
               | NW Int (Char -> Char -> Bool) Char
               | NE Int (Char -> Char -> Bool) Char
               | SW Int (Char -> Char -> Bool) Char
               | SE Int (Char -> Char -> Bool) Char
