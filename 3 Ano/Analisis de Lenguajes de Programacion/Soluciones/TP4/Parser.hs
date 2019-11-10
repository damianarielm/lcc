module Parser (Variable, Comm(..), IntExp(..), BoolExp(..), parser) where
import Data.Char
import AST
import Control.Applicative (Applicative(..))
import Control.Monad       (liftM, ap)  


-- parser produced by Happy Version 1.15

data HappyAbsSyn t4 t5 t6
	= HappyTerminal Token
	| HappyErrorToken Int
	| HappyAbsSyn4 t4
	| HappyAbsSyn5 t5
	| HappyAbsSyn6 t6

action_0 (8) = happyShift action_4
action_0 (25) = happyShift action_5
action_0 (29) = happyShift action_6
action_0 (31) = happyShift action_2
action_0 (4) = happyGoto action_3
action_0 _ = happyFail

action_1 (31) = happyShift action_2
action_1 _ = happyFail

action_2 _ = happyReduce_1

action_3 (23) = happyShift action_18
action_3 (32) = happyAccept
action_3 _ = happyFail

action_4 (24) = happyShift action_17
action_4 _ = happyFail

action_5 (7) = happyShift action_9
action_5 (8) = happyShift action_10
action_5 (9) = happyShift action_11
action_5 (13) = happyShift action_12
action_5 (15) = happyShift action_13
action_5 (16) = happyShift action_14
action_5 (20) = happyShift action_15
action_5 (5) = happyGoto action_7
action_5 (6) = happyGoto action_16
action_5 _ = happyFail

action_6 (7) = happyShift action_9
action_6 (8) = happyShift action_10
action_6 (9) = happyShift action_11
action_6 (13) = happyShift action_12
action_6 (15) = happyShift action_13
action_6 (16) = happyShift action_14
action_6 (20) = happyShift action_15
action_6 (5) = happyGoto action_7
action_6 (6) = happyGoto action_8
action_6 _ = happyFail

action_7 (9) = happyShift action_30
action_7 (10) = happyShift action_31
action_7 (11) = happyShift action_32
action_7 (12) = happyShift action_33
action_7 (17) = happyShift action_34
action_7 (18) = happyShift action_35
action_7 (19) = happyShift action_36
action_7 _ = happyFail

action_8 (21) = happyShift action_22
action_8 (22) = happyShift action_23
action_8 (30) = happyShift action_29
action_8 _ = happyFail

action_9 _ = happyReduce_6

action_10 _ = happyReduce_7

action_11 (7) = happyShift action_9
action_11 (8) = happyShift action_10
action_11 (9) = happyShift action_11
action_11 (13) = happyShift action_21
action_11 (5) = happyGoto action_28
action_11 _ = happyFail

action_12 (7) = happyShift action_9
action_12 (8) = happyShift action_10
action_12 (9) = happyShift action_11
action_12 (13) = happyShift action_12
action_12 (15) = happyShift action_13
action_12 (16) = happyShift action_14
action_12 (20) = happyShift action_15
action_12 (5) = happyGoto action_26
action_12 (6) = happyGoto action_27
action_12 _ = happyFail

action_13 _ = happyReduce_14

action_14 _ = happyReduce_15

action_15 (7) = happyShift action_9
action_15 (8) = happyShift action_10
action_15 (9) = happyShift action_11
action_15 (13) = happyShift action_12
action_15 (15) = happyShift action_13
action_15 (16) = happyShift action_14
action_15 (20) = happyShift action_15
action_15 (5) = happyGoto action_7
action_15 (6) = happyGoto action_25
action_15 _ = happyFail

action_16 (21) = happyShift action_22
action_16 (22) = happyShift action_23
action_16 (26) = happyShift action_24
action_16 _ = happyFail

action_17 (7) = happyShift action_9
action_17 (8) = happyShift action_10
action_17 (9) = happyShift action_11
action_17 (13) = happyShift action_21
action_17 (5) = happyGoto action_20
action_17 _ = happyFail

action_18 (8) = happyShift action_4
action_18 (25) = happyShift action_5
action_18 (29) = happyShift action_6
action_18 (31) = happyShift action_2
action_18 (4) = happyGoto action_19
action_18 _ = happyFail

action_19 _ = happyReduce_3

action_20 (9) = happyShift action_30
action_20 (10) = happyShift action_31
action_20 (11) = happyShift action_32
action_20 (12) = happyShift action_33
action_20 _ = happyReduce_2

action_21 (7) = happyShift action_9
action_21 (8) = happyShift action_10
action_21 (9) = happyShift action_11
action_21 (13) = happyShift action_21
action_21 (5) = happyGoto action_50
action_21 _ = happyFail

action_22 (7) = happyShift action_9
action_22 (8) = happyShift action_10
action_22 (9) = happyShift action_11
action_22 (13) = happyShift action_12
action_22 (15) = happyShift action_13
action_22 (16) = happyShift action_14
action_22 (20) = happyShift action_15
action_22 (5) = happyGoto action_7
action_22 (6) = happyGoto action_49
action_22 _ = happyFail

action_23 (7) = happyShift action_9
action_23 (8) = happyShift action_10
action_23 (9) = happyShift action_11
action_23 (13) = happyShift action_12
action_23 (15) = happyShift action_13
action_23 (16) = happyShift action_14
action_23 (20) = happyShift action_15
action_23 (5) = happyGoto action_7
action_23 (6) = happyGoto action_48
action_23 _ = happyFail

action_24 (8) = happyShift action_4
action_24 (25) = happyShift action_5
action_24 (29) = happyShift action_6
action_24 (31) = happyShift action_2
action_24 (4) = happyGoto action_47
action_24 _ = happyFail

action_25 _ = happyReduce_21

action_26 (9) = happyShift action_30
action_26 (10) = happyShift action_31
action_26 (11) = happyShift action_32
action_26 (12) = happyShift action_33
action_26 (14) = happyShift action_46
action_26 (17) = happyShift action_34
action_26 (18) = happyShift action_35
action_26 (19) = happyShift action_36
action_26 _ = happyFail

action_27 (14) = happyShift action_45
action_27 (21) = happyShift action_22
action_27 (22) = happyShift action_23
action_27 _ = happyFail

action_28 _ = happyReduce_8

action_29 (8) = happyShift action_4
action_29 (25) = happyShift action_5
action_29 (29) = happyShift action_6
action_29 (31) = happyShift action_2
action_29 (4) = happyGoto action_44
action_29 _ = happyFail

action_30 (7) = happyShift action_9
action_30 (8) = happyShift action_10
action_30 (9) = happyShift action_11
action_30 (13) = happyShift action_21
action_30 (5) = happyGoto action_43
action_30 _ = happyFail

action_31 (7) = happyShift action_9
action_31 (8) = happyShift action_10
action_31 (9) = happyShift action_11
action_31 (13) = happyShift action_21
action_31 (5) = happyGoto action_42
action_31 _ = happyFail

action_32 (7) = happyShift action_9
action_32 (8) = happyShift action_10
action_32 (9) = happyShift action_11
action_32 (13) = happyShift action_21
action_32 (5) = happyGoto action_41
action_32 _ = happyFail

action_33 (7) = happyShift action_9
action_33 (8) = happyShift action_10
action_33 (9) = happyShift action_11
action_33 (13) = happyShift action_21
action_33 (5) = happyGoto action_40
action_33 _ = happyFail

action_34 (7) = happyShift action_9
action_34 (8) = happyShift action_10
action_34 (9) = happyShift action_11
action_34 (13) = happyShift action_21
action_34 (5) = happyGoto action_39
action_34 _ = happyFail

action_35 (7) = happyShift action_9
action_35 (8) = happyShift action_10
action_35 (9) = happyShift action_11
action_35 (13) = happyShift action_21
action_35 (5) = happyGoto action_38
action_35 _ = happyFail

action_36 (7) = happyShift action_9
action_36 (8) = happyShift action_10
action_36 (9) = happyShift action_11
action_36 (13) = happyShift action_21
action_36 (5) = happyGoto action_37
action_36 _ = happyFail

action_37 (9) = happyShift action_30
action_37 (10) = happyShift action_31
action_37 (11) = happyShift action_32
action_37 (12) = happyShift action_33
action_37 _ = happyReduce_18

action_38 (9) = happyShift action_30
action_38 (10) = happyShift action_31
action_38 (11) = happyShift action_32
action_38 (12) = happyShift action_33
action_38 _ = happyReduce_17

action_39 (9) = happyShift action_30
action_39 (10) = happyShift action_31
action_39 (11) = happyShift action_32
action_39 (12) = happyShift action_33
action_39 _ = happyReduce_16

action_40 _ = happyReduce_12

action_41 _ = happyReduce_11

action_42 (11) = happyShift action_32
action_42 (12) = happyShift action_33
action_42 _ = happyReduce_9

action_43 (11) = happyShift action_32
action_43 (12) = happyShift action_33
action_43 _ = happyReduce_10

action_44 (23) = happyShift action_18
action_44 (28) = happyShift action_52
action_44 _ = happyFail

action_45 _ = happyReduce_22

action_46 _ = happyReduce_13

action_47 (23) = happyShift action_18
action_47 (27) = happyShift action_51
action_47 _ = happyFail

action_48 (21) = happyShift action_22
action_48 _ = happyReduce_20

action_49 _ = happyReduce_19

action_50 (9) = happyShift action_30
action_50 (10) = happyShift action_31
action_50 (11) = happyShift action_32
action_50 (12) = happyShift action_33
action_50 (14) = happyShift action_46
action_50 _ = happyFail

action_51 (8) = happyShift action_4
action_51 (25) = happyShift action_5
action_51 (29) = happyShift action_6
action_51 (31) = happyShift action_2
action_51 (4) = happyGoto action_53
action_51 _ = happyFail

action_52 _ = happyReduce_5

action_53 (23) = happyShift action_18
action_53 (28) = happyShift action_54
action_53 _ = happyFail

action_54 _ = happyReduce_4

happyReduce_1 = happySpecReduce_1 4 happyReduction_1
happyReduction_1 _
	 =  HappyAbsSyn4
		 (Skip
	)

happyReduce_2 = happySpecReduce_3 4 happyReduction_2
happyReduction_2 (HappyAbsSyn5  happy_var_3)
	_
	(HappyTerminal (TokenId happy_var_1))
	 =  HappyAbsSyn4
		 (Let happy_var_1 happy_var_3
	)
happyReduction_2 _ _ _  = notHappyAtAll 

happyReduce_3 = happySpecReduce_3 4 happyReduction_3
happyReduction_3 (HappyAbsSyn4  happy_var_3)
	_
	(HappyAbsSyn4  happy_var_1)
	 =  HappyAbsSyn4
		 (Seq happy_var_1 happy_var_3
	)
happyReduction_3 _ _ _  = notHappyAtAll 

happyReduce_4 = happyReduce 7 4 happyReduction_4
happyReduction_4 (_ `HappyStk`
	(HappyAbsSyn4  happy_var_6) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn4  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn6  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn4
		 (Cond happy_var_2 happy_var_4 happy_var_6
	) `HappyStk` happyRest

happyReduce_5 = happyReduce 5 4 happyReduction_5
happyReduction_5 (_ `HappyStk`
	(HappyAbsSyn4  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn6  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn4
		 (While happy_var_2 happy_var_4
	) `HappyStk` happyRest

happyReduce_6 = happySpecReduce_1 5 happyReduction_6
happyReduction_6 (HappyTerminal (TokenInt happy_var_1))
	 =  HappyAbsSyn5
		 (Const happy_var_1
	)
happyReduction_6 _  = notHappyAtAll 

happyReduce_7 = happySpecReduce_1 5 happyReduction_7
happyReduction_7 (HappyTerminal (TokenId happy_var_1))
	 =  HappyAbsSyn5
		 (Var happy_var_1
	)
happyReduction_7 _  = notHappyAtAll 

happyReduce_8 = happySpecReduce_2 5 happyReduction_8
happyReduction_8 (HappyAbsSyn5  happy_var_2)
	_
	 =  HappyAbsSyn5
		 (UMinus happy_var_2
	)
happyReduction_8 _ _  = notHappyAtAll 

happyReduce_9 = happySpecReduce_3 5 happyReduction_9
happyReduction_9 (HappyAbsSyn5  happy_var_3)
	_
	(HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn5
		 (Plus happy_var_1 happy_var_3
	)
happyReduction_9 _ _ _  = notHappyAtAll 

happyReduce_10 = happySpecReduce_3 5 happyReduction_10
happyReduction_10 (HappyAbsSyn5  happy_var_3)
	_
	(HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn5
		 (Minus happy_var_1 happy_var_3
	)
happyReduction_10 _ _ _  = notHappyAtAll 

happyReduce_11 = happySpecReduce_3 5 happyReduction_11
happyReduction_11 (HappyAbsSyn5  happy_var_3)
	_
	(HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn5
		 (Times happy_var_1 happy_var_3
	)
happyReduction_11 _ _ _  = notHappyAtAll 

happyReduce_12 = happySpecReduce_3 5 happyReduction_12
happyReduction_12 (HappyAbsSyn5  happy_var_3)
	_
	(HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn5
		 (Div happy_var_1 happy_var_3
	)
happyReduction_12 _ _ _  = notHappyAtAll 

happyReduce_13 = happySpecReduce_3 5 happyReduction_13
happyReduction_13 _
	(HappyAbsSyn5  happy_var_2)
	_
	 =  HappyAbsSyn5
		 (happy_var_2
	)
happyReduction_13 _ _ _  = notHappyAtAll 

happyReduce_14 = happySpecReduce_1 6 happyReduction_14
happyReduction_14 _
	 =  HappyAbsSyn6
		 (BTrue
	)

happyReduce_15 = happySpecReduce_1 6 happyReduction_15
happyReduction_15 _
	 =  HappyAbsSyn6
		 (BFalse
	)

happyReduce_16 = happySpecReduce_3 6 happyReduction_16
happyReduction_16 (HappyAbsSyn5  happy_var_3)
	_
	(HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn6
		 (Eq happy_var_1 happy_var_3
	)
happyReduction_16 _ _ _  = notHappyAtAll 

happyReduce_17 = happySpecReduce_3 6 happyReduction_17
happyReduction_17 (HappyAbsSyn5  happy_var_3)
	_
	(HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn6
		 (Lt happy_var_1 happy_var_3
	)
happyReduction_17 _ _ _  = notHappyAtAll 

happyReduce_18 = happySpecReduce_3 6 happyReduction_18
happyReduction_18 (HappyAbsSyn5  happy_var_3)
	_
	(HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn6
		 (Gt happy_var_1 happy_var_3
	)
happyReduction_18 _ _ _  = notHappyAtAll 

happyReduce_19 = happySpecReduce_3 6 happyReduction_19
happyReduction_19 (HappyAbsSyn6  happy_var_3)
	_
	(HappyAbsSyn6  happy_var_1)
	 =  HappyAbsSyn6
		 (And happy_var_1 happy_var_3
	)
happyReduction_19 _ _ _  = notHappyAtAll 

happyReduce_20 = happySpecReduce_3 6 happyReduction_20
happyReduction_20 (HappyAbsSyn6  happy_var_3)
	_
	(HappyAbsSyn6  happy_var_1)
	 =  HappyAbsSyn6
		 (Or happy_var_1 happy_var_3
	)
happyReduction_20 _ _ _  = notHappyAtAll 

happyReduce_21 = happySpecReduce_2 6 happyReduction_21
happyReduction_21 (HappyAbsSyn6  happy_var_2)
	_
	 =  HappyAbsSyn6
		 (Not happy_var_2
	)
happyReduction_21 _ _  = notHappyAtAll 

happyReduce_22 = happySpecReduce_3 6 happyReduction_22
happyReduction_22 _
	(HappyAbsSyn6  happy_var_2)
	_
	 =  HappyAbsSyn6
		 (happy_var_2
	)
happyReduction_22 _ _ _  = notHappyAtAll 

happyNewToken action sts stk [] =
	action 32 32 (error "reading EOF!") (HappyState action) sts stk []

happyNewToken action sts stk (tk:tks) =
	let cont i = action i i tk (HappyState action) sts stk tks in
	case tk of {
	TokenInt happy_dollar_dollar -> cont 7;
	TokenId happy_dollar_dollar -> cont 8;
	TokenMinus -> cont 9;
	TokenPlus -> cont 10;
	TokenTimes -> cont 11;
	TokenDiv -> cont 12;
	TokenLPar -> cont 13;
	TokenRPar -> cont 14;
	TokenTrue -> cont 15;
	TokenFalse -> cont 16;
	TokenEq -> cont 17;
	TokenLt -> cont 18;
	TokenGt -> cont 19;
	TokenNot -> cont 20;
	TokenAnd -> cont 21;
	TokenOr -> cont 22;
	TokenSeq -> cont 23;
	TokenIs -> cont 24;
	TokenIf -> cont 25;
	TokenThen -> cont 26;
	TokenElse -> cont 27;
	TokenEnd -> cont 28;
	TokenWhile -> cont 29;
	TokenDo -> cont 30;
	TokenSkip -> cont 31;
--	_ -> happyError' (tk:tks)
	}

happyError_ tk tks = happyError' (tk:tks)

newtype HappyIdentity a = HappyIdentity a
happyIdentity = HappyIdentity
happyRunIdentity (HappyIdentity a) = a

instance Monad HappyIdentity where
    return = HappyIdentity
    (HappyIdentity p) >>= q = q p

-- Para calmar al GHC
instance Functor HappyIdentity where
    fmap = liftM
 
instance Applicative HappyIdentity where
    pure   = return
    (<*>)  = ap      


happyThen :: () => HappyIdentity a -> (a -> HappyIdentity b) -> HappyIdentity b
happyThen = (>>=)
happyReturn :: () => a -> HappyIdentity a
happyReturn = (return)
happyThen1 m k tks = (>>=) m (\a -> k a tks)
happyReturn1 :: () => a -> b -> HappyIdentity a
happyReturn1 = \a tks -> (return) a
happyError' :: () => [Token] -> HappyIdentity a
happyError' = HappyIdentity . happyError

parse tks = happyRunIdentity happySomeParser where
  happySomeParser = happyThen (happyParse action_0 tks) (\x -> case x of {HappyAbsSyn4 z -> happyReturn z; _other -> notHappyAtAll })

happySeq = happyDontSeq

happyError :: [Token] -> a
happyError _ = error "Error sintactico"

data Token = TokenInt Int
	   | TokenId Variable
	   | TokenMinus
	   | TokenPlus
	   | TokenTimes
	   | TokenDiv
	   | TokenLPar
	   | TokenRPar
	   | TokenTrue
	   | TokenFalse
	   | TokenEq
	   | TokenLt
	   | TokenGt
	   | TokenNot
	   | TokenAnd
	   | TokenOr
	   | TokenSeq
	   | TokenIs
	   | TokenIf
	   | TokenThen
	   | TokenElse
	   | TokenEnd
	   | TokenWhile
	   | TokenDo
	   | TokenSkip
 deriving Show

-- Analizador Lexicografico
lexer :: String -> [Token]
lexer [] = []
lexer (c:cs) 
      | isSpace c = lexer cs
      | isAlpha c = lexAlpha (c:cs)
      | isDigit c = lexNum (c:cs)
lexer (':':cs) = lexAssignment cs
lexer ('-':cs) = TokenMinus : lexer cs
lexer ('+':cs) = TokenPlus : lexer cs
lexer ('*':cs) = TokenTimes : lexer cs
lexer ('/':cs) = TokenDiv : lexer cs
lexer ('(':cs) = TokenLPar : lexer cs
lexer (')':cs) = TokenRPar : lexer cs
lexer ('=':cs) = TokenEq : lexer cs
lexer ('<':cs) = TokenLt : lexer cs
lexer ('>':cs) = TokenGt : lexer cs
lexer ('~':cs) = TokenNot : lexer cs
lexer ('&':cs) = TokenAnd : lexer cs
lexer ('|':cs) = TokenOr : lexer cs
lexer (';':cs) = TokenSeq : lexer cs

lexAlpha cs =
   case span isAlpha cs of
	    ("true",rest)  -> TokenTrue : lexer rest
	    ("false",rest) -> TokenFalse : lexer rest
	    ("skip",rest)  -> TokenSkip : lexer rest
	    ("if",rest)    -> TokenIf : lexer rest
	    ("then",rest)  -> TokenThen : lexer rest
	    ("else",rest)  -> TokenElse : lexer rest
	    ("end",rest)   -> TokenEnd : lexer rest	    
	    ("while",rest) -> TokenWhile : lexer rest
	    ("do",rest)    -> TokenDo : lexer rest
	    (var,rest)     -> TokenId var : lexer rest

lexNum :: String -> [Token]
lexNum cs = TokenInt (readNum num) : lexer rest
      where (num,rest) = span isDigit cs

readNum :: String -> Int
readNum ds = foldl1 (\n d -> 10 * n + d) (map digToInt ds)
	     where digToInt d = fromEnum d - fromEnum '0'

lexAssignment :: String -> [Token]
lexAssignment ('=':cs) = TokenIs : lexer cs
lexAssignment _ = error "Parse Error"

parser = parse . lexer
{-# LINE 1 "GenericTemplate.hs" #-}
-- $Id$

{-# LINE 15 "GenericTemplate.hs" #-}






















































infixr 9 `HappyStk`
data HappyStk a = HappyStk a (HappyStk a)

-----------------------------------------------------------------------------
-- starting the parse

happyParse start_state = happyNewToken start_state notHappyAtAll notHappyAtAll

-----------------------------------------------------------------------------
-- Accepting the parse

-- If the current token is (1), it means we've just accepted a partial
-- parse (a %partial parser).  We must ignore the saved token on the top of
-- the stack in this case.
happyAccept (1) tk st sts (_ `HappyStk` ans `HappyStk` _) =
	happyReturn1 ans
happyAccept j tk st sts (HappyStk ans _) = 
	 (happyReturn1 ans)

-----------------------------------------------------------------------------
-- Arrays only: do the next action

{-# LINE 154 "GenericTemplate.hs" #-}


-----------------------------------------------------------------------------
-- HappyState data type (not arrays)



newtype HappyState b c = HappyState
        (Int ->                    -- token number
         Int ->                    -- token number (yes, again)
         b ->                           -- token semantic value
         HappyState b c ->              -- current state
         [HappyState b c] ->            -- state stack
         c)



-----------------------------------------------------------------------------
-- Shifting a token

happyShift new_state (1) tk st sts stk@(x `HappyStk` _) =
     let i = (case x of { HappyErrorToken (i) -> i }) in
--     trace "shifting the error token" $
     new_state i i tk (HappyState (new_state)) ((st):(sts)) (stk)

happyShift new_state i tk st sts stk =
     happyNewToken new_state ((st):(sts)) ((HappyTerminal (tk))`HappyStk`stk)

-- happyReduce is specialised for the common cases.

happySpecReduce_0 i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happySpecReduce_0 nt fn j tk st@((HappyState (action))) sts stk
     = action nt j tk st ((st):(sts)) (fn `HappyStk` stk)

happySpecReduce_1 i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happySpecReduce_1 nt fn j tk _ sts@(((st@(HappyState (action))):(_))) (v1`HappyStk`stk')
     = let r = fn v1 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happySpecReduce_2 i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happySpecReduce_2 nt fn j tk _ ((_):(sts@(((st@(HappyState (action))):(_))))) (v1`HappyStk`v2`HappyStk`stk')
     = let r = fn v1 v2 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happySpecReduce_3 i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happySpecReduce_3 nt fn j tk _ ((_):(((_):(sts@(((st@(HappyState (action))):(_))))))) (v1`HappyStk`v2`HappyStk`v3`HappyStk`stk')
     = let r = fn v1 v2 v3 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happyReduce k i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happyReduce k nt fn j tk st sts stk
     = case happyDrop (k - ((1) :: Int)) sts of
	 sts1@(((st1@(HappyState (action))):(_))) ->
        	let r = fn stk in  -- it doesn't hurt to always seq here...
       		happyDoSeq r (action nt j tk st1 sts1 r)

happyMonadReduce k nt fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happyMonadReduce k nt fn j tk st sts stk =
        happyThen1 (fn stk) (\r -> action nt j tk st1 sts1 (r `HappyStk` drop_stk))
       where sts1@(((st1@(HappyState (action))):(_))) = happyDrop k ((st):(sts))
             drop_stk = happyDropStk k stk

happyDrop (0) l = l
happyDrop n ((_):(t)) = happyDrop (n - ((1) :: Int)) t

happyDropStk (0) l = l
happyDropStk n (x `HappyStk` xs) = happyDropStk (n - ((1)::Int)) xs

-----------------------------------------------------------------------------
-- Moving to a new state after a reduction









happyGoto action j tk st = action j j tk (HappyState action)


-----------------------------------------------------------------------------
-- Error recovery ((1) is the error token)

-- parse error if we are in recovery and we fail again
happyFail  (1) tk old_st _ stk =
--	trace "failing" $ 
    	happyError_ tk

{-  We don't need state discarding for our restricted implementation of
    "error".  In fact, it can cause some bogus parses, so I've disabled it
    for now --SDM

-- discard a state
happyFail  (1) tk old_st (((HappyState (action))):(sts)) 
						(saved_tok `HappyStk` _ `HappyStk` stk) =
--	trace ("discarding state, depth " ++ show (length stk))  $
	action (1) (1) tk (HappyState (action)) sts ((saved_tok`HappyStk`stk))
-}

-- Enter error recovery: generate an error token,
--                       save the old token and carry on.
happyFail  i tk (HappyState (action)) sts stk =
--      trace "entering error recovery" $
	action (1) (1) tk (HappyState (action)) sts ( (HappyErrorToken (i)) `HappyStk` stk)

-- Internal happy errors:

notHappyAtAll = error "Internal Happy error\n"

-----------------------------------------------------------------------------
-- Hack to get the typechecker to accept our action functions







-----------------------------------------------------------------------------
-- Seq-ing.  If the --strict flag is given, then Happy emits 
--	happySeq = happyDoSeq
-- otherwise it emits
-- 	happySeq = happyDontSeq

happyDoSeq, happyDontSeq :: a -> b -> b
happyDoSeq   a b = a `seq` b
happyDontSeq a b = b

-----------------------------------------------------------------------------
-- Don't inline any functions from the template.  GHC has a nasty habit
-- of deciding to inline happyGoto everywhere, which increases the size of
-- the generated parser quite a bit.









{-# NOINLINE happyShift #-}
{-# NOINLINE happySpecReduce_0 #-}
{-# NOINLINE happySpecReduce_1 #-}
{-# NOINLINE happySpecReduce_2 #-}
{-# NOINLINE happySpecReduce_3 #-}
{-# NOINLINE happyReduce #-}
{-# NOINLINE happyMonadReduce #-}
{-# NOINLINE happyGoto #-}
{-# NOINLINE happyFail #-}

-- end of Happy Template.
