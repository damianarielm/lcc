{
{-# LANGUAGE RankNTypes #-}

module Parser where

import Types 
import Data.Char (isAlpha, isDigit, isSpace)
import UI.NCurses (Color (..))
}

%name parse
%tokentype { Token }
%error { error "Error de parseo en definicion de automata" }

%token
  Chebyshev     { TChebyshev }
  Manhattan     { TManhattan }
  State         { TState }
  Black         { TBlack }
  Red           { TRed }
  Green         { TGreen }
  Yellow        { TYellow }
  Blue          { TBlue }
  Magenta       { TMagenta }
  Cyan          { TCyan }
  White         { TWhite }
  ':'           { TColon }
  ','           { TSemiColon }
  '\''          { TApostrophe }
  '('           { TPOpen }
  ')'           { TPClose }
  Int           { TInt $$ }
  Char          { TChar $$ }
  Eq            { TEq }
  Neq           { TNeq }
  Leq           { TLeq }
  Geq           { TGeq }
  Lower         { TLower }
  Greater       { TGreater }
  And           { TAnd } 
  North         { TNorth }
  South         { TSouth }
  East          { TEast }
  West          { TWest }
  NW            { TNW }
  NE            { TNE }
  SE            { TSE }
  SW            { TSW }

%left '\''
%right ':'
%left And
%right Char
%%

Automata   ::                                                               { ([State], [Rule]) }
Automata   : States Rules                                                   { ($1, $2) }

States     ::                                                               { [State] }
States     : '\'' Char '\'' ':' '\'' Char '\'' Color Color States           { ($2, $6, $8, $9) : $10 }
           | {- empty -}                                                    { [] }

Color      ::                                                               { Color }
Color      : Black                                                          { ColorBlack }
           | Red                                                            { ColorRed }
           | Green                                                          { ColorGreen }
           | Yellow                                                         { ColorYellow }
           | Blue                                                           { ColorBlue }
           | Magenta                                                        { ColorMagenta }
           | Cyan                                                           { ColorCyan }
           | White                                                          { ColorWhite }

Rules      ::                                                               { [Rule] }
Rules      : State Eq '\'' Char '\'' ':' '\'' Char '\'' Rules               { ($4,[], $8) : $10 }
	   | State Eq '\'' Char '\'' And Comparsion ':' '\'' Char '\'' Rules{ ($4, $7, $10) : $12  }
           | {- empty -}                                                    { [] }

Comparsion ::                                                               { [Condition] }
Comparsion : Distance '(' '\'' Char '\'' ',' Int ')' Cmp Int Comparsion     { ($1 $4 $7 $9 $10) : $11 } 
           | Cardinal '(' Int ')' Cmp '\'' Char '\'' Comparsion             { ($1 $3 $5 $7) : $9 }
           | {- empty -}                                                    { [] }

Distance   ::                                                               { Char -> Int -> (Int -> Int -> Bool) -> Int -> Condition }
Distance   : Chebyshev                                                      { Chebyshev }
	   | Manhattan                                                      { Manhattan }

Cardinal   ::                                                               { Int -> (Char -> Char -> Bool) -> Char -> Condition } 
Cardinal   : North                                                          { North }
	   | South                                                          { South }
           | East                                                           { East }
           | West                                                           { West }
           | NE                                                             { NE }
           | NW                                                             { NW }
           | SE                                                             { SE }
           | SW                                                             { SW }

Cmp        ::                                                               { forall a. (Ord a) => a -> a -> Bool }
Cmp        : Eq                                                             { (==) }
	   | Leq                                                            { (<=) }
           | Geq                                                            { (>=) }
           | Lower                                                          { (<)  }
           | Greater                                                        { (>)  }
           | Neq                                                            { (/=) }

{
lexer :: String -> [Token]
lexer [] = []
lexer ('\'':c:'\'':cs) = TApostrophe : (TChar c) : TApostrophe : lexer cs
lexer ('&':'&':cs) = TAnd : lexer cs
lexer ('=':'=':cs) = TEq : lexer cs
lexer ('/':'=':cs) = TNeq : lexer cs
lexer ('>':'=':cs) = TGeq : lexer cs
lexer ('<':'=':cs) = TLeq : lexer cs
lexer ('<':cs)     = TLower : lexer cs
lexer ('>':cs)     = TGreater : lexer cs
lexer ('(':cs)     = TPOpen : lexer cs
lexer (')':cs)     = TPClose : lexer cs
lexer (',':cs)     = TSemiColon : lexer cs
lexer (':':cs)     = TColon : lexer cs
lexer (c:cs)
      | isSpace c  = lexer cs
      | isAlpha c  = lexVar (c:cs)
      | isDigit c  = lexNum (c:cs)

lexNum cs = TInt (read num) : lexer rest where
            (num, rest) = span isDigit cs

lexVar cs = case span isAlpha cs of
            ("Neighbours", rest) -> TNeighbours : lexer rest
            ("Chebyshev", rest)  -> TChebyshev : lexer rest
            ("Manhattan", rest)  -> TManhattan : lexer rest
            ("State", rest)      -> TState : lexer rest
            ("Black", rest)      -> TBlack : lexer rest
            ("Red", rest)        -> TRed : lexer rest
            ("Green", rest)      -> TGreen : lexer rest
            ("Yellow", rest)     -> TYellow : lexer rest
            ("Blue", rest)       -> TBlue : lexer rest
            ("Magenta", rest)    -> TMagenta : lexer rest
            ("Cyan", rest)       -> TCyan : lexer rest
            ("White", rest)      -> TWhite : lexer rest
            ("North", rest)      -> TNorth : lexer rest
            ("South", rest)      -> TSouth : lexer rest
            ("East", rest)       -> TEast : lexer rest
            ("West", rest)       -> TWest : lexer rest
            ("NW", rest)         -> TNW : lexer rest
            ("NE", rest)         -> TNE : lexer rest
            ("SW", rest)         -> TSW : lexer rest
            ("SE", rest)         -> TSE : lexer rest
}
