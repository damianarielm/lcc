{-# OPTIONS_GHC -w #-}
module Parse where
import Common
import Data.Maybe
import Data.Char
import qualified Data.Array as Happy_Data_Array
import qualified Data.Bits as Bits
import Control.Applicative(Applicative(..))
import Control.Monad (ap)

-- parser produced by Happy Version 1.19.11

data HappyAbsSyn t6 t7 t11 t12
	= HappyTerminal (Token)
	| HappyErrorToken Int
	| HappyAbsSyn6 t6
	| HappyAbsSyn7 t7
	| HappyAbsSyn8 (LamTerm)
	| HappyAbsSyn11 t11
	| HappyAbsSyn12 t12

happyExpList :: Happy_Data_Array.Array Int Int
happyExpList = Happy_Data_Array.listArray (0,114) ([16384,7377,0,16,5120,457,0,1,0,0,1024,0,8192,0,4164,0,0,0,4,5120,457,0,0,4096,0,0,0,51476,1,29253,0,64,0,0,0,0,0,8,8448,4,0,0,0,0,0,4096,0,32768,130,512,0,0,0,37184,28,4,0,51476,1,2056,0,1057,0,0,5120,457,17664,114,1024,0,2112,1,0,0,0,0,14,16384,264,0,48,2048,8,1152,0,32768,0,51476,1,0,16384,7313,0,1,0,0,33792,16,1536,0,32768,0,8192,0,0,0
	])

{-# NOINLINE happyExpListPerState #-}
happyExpListPerState st =
    token_strs_expected
  where token_strs = ["error","%dummy","%start_parseStmt","%start_parseStmts","%start_term","Def","Defexp","Exp","NAbs","Atom","Type","Defs","'='","':'","'\\\\'","'.'","'('","')'","'->'","','","VAR","TYPE","DEF","LET","IN","AS","UNIT","FST","SND","%eof"]
        bit_start = st * 30
        bit_end = (st + 1) * 30
        read_bit = readArrayBit happyExpList
        bits = map read_bit [bit_start..bit_end - 1]
        bits_indexed = zip bits [0..29]
        token_strs_expected = concatMap f bits_indexed
        f (False, _) = []
        f (True, nr) = [token_strs !! nr]

action_0 (15) = happyShift action_9
action_0 (17) = happyShift action_10
action_0 (21) = happyShift action_11
action_0 (23) = happyShift action_5
action_0 (24) = happyShift action_12
action_0 (27) = happyShift action_13
action_0 (28) = happyShift action_14
action_0 (29) = happyShift action_15
action_0 (6) = happyGoto action_18
action_0 (7) = happyGoto action_4
action_0 (8) = happyGoto action_19
action_0 (9) = happyGoto action_7
action_0 (10) = happyGoto action_8
action_0 _ = happyFail (happyExpListPerState 0)

action_1 (23) = happyShift action_5
action_1 (7) = happyGoto action_16
action_1 (12) = happyGoto action_17
action_1 _ = happyReduce_24

action_2 (15) = happyShift action_9
action_2 (17) = happyShift action_10
action_2 (21) = happyShift action_11
action_2 (24) = happyShift action_12
action_2 (27) = happyShift action_13
action_2 (28) = happyShift action_14
action_2 (29) = happyShift action_15
action_2 (8) = happyGoto action_6
action_2 (9) = happyGoto action_7
action_2 (10) = happyGoto action_8
action_2 _ = happyFail (happyExpListPerState 2)

action_3 (23) = happyShift action_5
action_3 (7) = happyGoto action_4
action_3 _ = happyFail (happyExpListPerState 3)

action_4 _ = happyReduce_3

action_5 (21) = happyShift action_29
action_5 _ = happyFail (happyExpListPerState 5)

action_6 (26) = happyShift action_20
action_6 (30) = happyAccept
action_6 _ = happyFail (happyExpListPerState 6)

action_7 (17) = happyShift action_28
action_7 (21) = happyShift action_11
action_7 (27) = happyShift action_13
action_7 (10) = happyGoto action_27
action_7 _ = happyReduce_12

action_8 _ = happyReduce_14

action_9 (21) = happyShift action_26
action_9 _ = happyFail (happyExpListPerState 9)

action_10 (15) = happyShift action_9
action_10 (17) = happyShift action_10
action_10 (21) = happyShift action_11
action_10 (24) = happyShift action_12
action_10 (27) = happyShift action_13
action_10 (28) = happyShift action_14
action_10 (29) = happyShift action_15
action_10 (8) = happyGoto action_25
action_10 (9) = happyGoto action_7
action_10 (10) = happyGoto action_8
action_10 _ = happyFail (happyExpListPerState 10)

action_11 _ = happyReduce_15

action_12 (21) = happyShift action_24
action_12 _ = happyFail (happyExpListPerState 12)

action_13 _ = happyReduce_16

action_14 (15) = happyShift action_9
action_14 (17) = happyShift action_10
action_14 (21) = happyShift action_11
action_14 (24) = happyShift action_12
action_14 (27) = happyShift action_13
action_14 (28) = happyShift action_14
action_14 (29) = happyShift action_15
action_14 (8) = happyGoto action_23
action_14 (9) = happyGoto action_7
action_14 (10) = happyGoto action_8
action_14 _ = happyFail (happyExpListPerState 14)

action_15 (15) = happyShift action_9
action_15 (17) = happyShift action_10
action_15 (21) = happyShift action_11
action_15 (24) = happyShift action_12
action_15 (27) = happyShift action_13
action_15 (28) = happyShift action_14
action_15 (29) = happyShift action_15
action_15 (8) = happyGoto action_22
action_15 (9) = happyGoto action_7
action_15 (10) = happyGoto action_8
action_15 _ = happyFail (happyExpListPerState 15)

action_16 (23) = happyShift action_5
action_16 (7) = happyGoto action_16
action_16 (12) = happyGoto action_21
action_16 _ = happyReduce_24

action_17 (30) = happyAccept
action_17 _ = happyFail (happyExpListPerState 17)

action_18 (30) = happyAccept
action_18 _ = happyFail (happyExpListPerState 18)

action_19 (26) = happyShift action_20
action_19 _ = happyReduce_4

action_20 (17) = happyShift action_37
action_20 (22) = happyShift action_38
action_20 (27) = happyShift action_39
action_20 (11) = happyGoto action_36
action_20 _ = happyFail (happyExpListPerState 20)

action_21 _ = happyReduce_23

action_22 _ = happyReduce_10

action_23 _ = happyReduce_9

action_24 (13) = happyShift action_35
action_24 _ = happyFail (happyExpListPerState 24)

action_25 (18) = happyShift action_33
action_25 (20) = happyShift action_34
action_25 (26) = happyShift action_20
action_25 _ = happyFail (happyExpListPerState 25)

action_26 (14) = happyShift action_32
action_26 _ = happyFail (happyExpListPerState 26)

action_27 _ = happyReduce_13

action_28 (15) = happyShift action_9
action_28 (17) = happyShift action_10
action_28 (21) = happyShift action_11
action_28 (24) = happyShift action_12
action_28 (27) = happyShift action_13
action_28 (28) = happyShift action_14
action_28 (29) = happyShift action_15
action_28 (8) = happyGoto action_31
action_28 (9) = happyGoto action_7
action_28 (10) = happyGoto action_8
action_28 _ = happyFail (happyExpListPerState 28)

action_29 (13) = happyShift action_30
action_29 _ = happyFail (happyExpListPerState 29)

action_30 (15) = happyShift action_9
action_30 (17) = happyShift action_10
action_30 (21) = happyShift action_11
action_30 (24) = happyShift action_12
action_30 (27) = happyShift action_13
action_30 (28) = happyShift action_14
action_30 (29) = happyShift action_15
action_30 (8) = happyGoto action_45
action_30 (9) = happyGoto action_7
action_30 (10) = happyGoto action_8
action_30 _ = happyFail (happyExpListPerState 30)

action_31 (18) = happyShift action_33
action_31 (26) = happyShift action_20
action_31 _ = happyFail (happyExpListPerState 31)

action_32 (17) = happyShift action_37
action_32 (22) = happyShift action_38
action_32 (27) = happyShift action_39
action_32 (11) = happyGoto action_44
action_32 _ = happyFail (happyExpListPerState 32)

action_33 _ = happyReduce_17

action_34 (15) = happyShift action_9
action_34 (17) = happyShift action_10
action_34 (21) = happyShift action_11
action_34 (24) = happyShift action_12
action_34 (27) = happyShift action_13
action_34 (28) = happyShift action_14
action_34 (29) = happyShift action_15
action_34 (8) = happyGoto action_43
action_34 (9) = happyGoto action_7
action_34 (10) = happyGoto action_8
action_34 _ = happyFail (happyExpListPerState 34)

action_35 (15) = happyShift action_9
action_35 (17) = happyShift action_10
action_35 (21) = happyShift action_11
action_35 (24) = happyShift action_12
action_35 (27) = happyShift action_13
action_35 (28) = happyShift action_14
action_35 (29) = happyShift action_15
action_35 (8) = happyGoto action_42
action_35 (9) = happyGoto action_7
action_35 (10) = happyGoto action_8
action_35 _ = happyFail (happyExpListPerState 35)

action_36 (19) = happyShift action_41
action_36 _ = happyReduce_8

action_37 (17) = happyShift action_37
action_37 (22) = happyShift action_38
action_37 (27) = happyShift action_39
action_37 (11) = happyGoto action_40
action_37 _ = happyFail (happyExpListPerState 37)

action_38 _ = happyReduce_18

action_39 _ = happyReduce_21

action_40 (18) = happyShift action_50
action_40 (19) = happyShift action_41
action_40 (20) = happyShift action_51
action_40 _ = happyFail (happyExpListPerState 40)

action_41 (17) = happyShift action_37
action_41 (22) = happyShift action_38
action_41 (27) = happyShift action_39
action_41 (11) = happyGoto action_49
action_41 _ = happyFail (happyExpListPerState 41)

action_42 (25) = happyShift action_48
action_42 (26) = happyShift action_20
action_42 _ = happyFail (happyExpListPerState 42)

action_43 (18) = happyShift action_47
action_43 (26) = happyShift action_20
action_43 _ = happyFail (happyExpListPerState 43)

action_44 (16) = happyShift action_46
action_44 (19) = happyShift action_41
action_44 _ = happyFail (happyExpListPerState 44)

action_45 (26) = happyShift action_20
action_45 _ = happyReduce_5

action_46 (15) = happyShift action_9
action_46 (17) = happyShift action_10
action_46 (21) = happyShift action_11
action_46 (24) = happyShift action_12
action_46 (27) = happyShift action_13
action_46 (28) = happyShift action_14
action_46 (29) = happyShift action_15
action_46 (8) = happyGoto action_54
action_46 (9) = happyGoto action_7
action_46 (10) = happyGoto action_8
action_46 _ = happyFail (happyExpListPerState 46)

action_47 _ = happyReduce_11

action_48 (15) = happyShift action_9
action_48 (17) = happyShift action_10
action_48 (21) = happyShift action_11
action_48 (24) = happyShift action_12
action_48 (27) = happyShift action_13
action_48 (28) = happyShift action_14
action_48 (29) = happyShift action_15
action_48 (8) = happyGoto action_53
action_48 (9) = happyGoto action_7
action_48 (10) = happyGoto action_8
action_48 _ = happyFail (happyExpListPerState 48)

action_49 (19) = happyShift action_41
action_49 _ = happyReduce_19

action_50 _ = happyReduce_20

action_51 (17) = happyShift action_37
action_51 (22) = happyShift action_38
action_51 (27) = happyShift action_39
action_51 (11) = happyGoto action_52
action_51 _ = happyFail (happyExpListPerState 51)

action_52 (18) = happyShift action_55
action_52 (19) = happyShift action_41
action_52 _ = happyFail (happyExpListPerState 52)

action_53 (26) = happyShift action_20
action_53 _ = happyReduce_7

action_54 (26) = happyShift action_20
action_54 _ = happyReduce_6

action_55 _ = happyReduce_22

happyReduce_3 = happySpecReduce_1  6 happyReduction_3
happyReduction_3 (HappyAbsSyn7  happy_var_1)
	 =  HappyAbsSyn6
		 (happy_var_1
	)
happyReduction_3 _  = notHappyAtAll 

happyReduce_4 = happySpecReduce_1  6 happyReduction_4
happyReduction_4 (HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn6
		 (Eval happy_var_1
	)
happyReduction_4 _  = notHappyAtAll 

happyReduce_5 = happyReduce 4 7 happyReduction_5
happyReduction_5 ((HappyAbsSyn8  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TVar happy_var_2)) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn7
		 (Def happy_var_2 happy_var_4
	) `HappyStk` happyRest

happyReduce_6 = happyReduce 6 8 happyReduction_6
happyReduction_6 ((HappyAbsSyn8  happy_var_6) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn11  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TVar happy_var_2)) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn8
		 (Abs happy_var_2 happy_var_4 happy_var_6
	) `HappyStk` happyRest

happyReduce_7 = happyReduce 6 8 happyReduction_7
happyReduction_7 ((HappyAbsSyn8  happy_var_6) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn8  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TVar happy_var_2)) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn8
		 (LetL happy_var_2 happy_var_4 happy_var_6
	) `HappyStk` happyRest

happyReduce_8 = happySpecReduce_3  8 happyReduction_8
happyReduction_8 (HappyAbsSyn11  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (AsL happy_var_1 happy_var_3
	)
happyReduction_8 _ _ _  = notHappyAtAll 

happyReduce_9 = happySpecReduce_2  8 happyReduction_9
happyReduction_9 (HappyAbsSyn8  happy_var_2)
	_
	 =  HappyAbsSyn8
		 (FstL happy_var_2
	)
happyReduction_9 _ _  = notHappyAtAll 

happyReduce_10 = happySpecReduce_2  8 happyReduction_10
happyReduction_10 (HappyAbsSyn8  happy_var_2)
	_
	 =  HappyAbsSyn8
		 (SndL happy_var_2
	)
happyReduction_10 _ _  = notHappyAtAll 

happyReduce_11 = happyReduce 5 8 happyReduction_11
happyReduction_11 (_ `HappyStk`
	(HappyAbsSyn8  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn8  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn8
		 (PairL happy_var_2 happy_var_4
	) `HappyStk` happyRest

happyReduce_12 = happySpecReduce_1  8 happyReduction_12
happyReduction_12 (HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (happy_var_1
	)
happyReduction_12 _  = notHappyAtAll 

happyReduce_13 = happySpecReduce_2  9 happyReduction_13
happyReduction_13 (HappyAbsSyn8  happy_var_2)
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (App happy_var_1 happy_var_2
	)
happyReduction_13 _ _  = notHappyAtAll 

happyReduce_14 = happySpecReduce_1  9 happyReduction_14
happyReduction_14 (HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (happy_var_1
	)
happyReduction_14 _  = notHappyAtAll 

happyReduce_15 = happySpecReduce_1  10 happyReduction_15
happyReduction_15 (HappyTerminal (TVar happy_var_1))
	 =  HappyAbsSyn8
		 (LVar happy_var_1
	)
happyReduction_15 _  = notHappyAtAll 

happyReduce_16 = happySpecReduce_1  10 happyReduction_16
happyReduction_16 _
	 =  HappyAbsSyn8
		 (UnitL
	)

happyReduce_17 = happySpecReduce_3  10 happyReduction_17
happyReduction_17 _
	(HappyAbsSyn8  happy_var_2)
	_
	 =  HappyAbsSyn8
		 (happy_var_2
	)
happyReduction_17 _ _ _  = notHappyAtAll 

happyReduce_18 = happySpecReduce_1  11 happyReduction_18
happyReduction_18 _
	 =  HappyAbsSyn11
		 (Base
	)

happyReduce_19 = happySpecReduce_3  11 happyReduction_19
happyReduction_19 (HappyAbsSyn11  happy_var_3)
	_
	(HappyAbsSyn11  happy_var_1)
	 =  HappyAbsSyn11
		 (Fun happy_var_1 happy_var_3
	)
happyReduction_19 _ _ _  = notHappyAtAll 

happyReduce_20 = happySpecReduce_3  11 happyReduction_20
happyReduction_20 _
	(HappyAbsSyn11  happy_var_2)
	_
	 =  HappyAbsSyn11
		 (happy_var_2
	)
happyReduction_20 _ _ _  = notHappyAtAll 

happyReduce_21 = happySpecReduce_1  11 happyReduction_21
happyReduction_21 _
	 =  HappyAbsSyn11
		 (UnitT
	)

happyReduce_22 = happyReduce 5 11 happyReduction_22
happyReduction_22 (_ `HappyStk`
	(HappyAbsSyn11  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn11  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn11
		 (PairT happy_var_2 happy_var_4
	) `HappyStk` happyRest

happyReduce_23 = happySpecReduce_2  12 happyReduction_23
happyReduction_23 (HappyAbsSyn12  happy_var_2)
	(HappyAbsSyn7  happy_var_1)
	 =  HappyAbsSyn12
		 (happy_var_1 : happy_var_2
	)
happyReduction_23 _ _  = notHappyAtAll 

happyReduce_24 = happySpecReduce_0  12 happyReduction_24
happyReduction_24  =  HappyAbsSyn12
		 ([]
	)

happyNewToken action sts stk
	= lexer(\tk -> 
	let cont i = action i i tk (HappyState action) sts stk in
	case tk of {
	TEOF -> action 30 30 tk (HappyState action) sts stk;
	TEquals -> cont 13;
	TColon -> cont 14;
	TAbs -> cont 15;
	TDot -> cont 16;
	TOpen -> cont 17;
	TClose -> cont 18;
	TArrow -> cont 19;
	TComma -> cont 20;
	TVar happy_dollar_dollar -> cont 21;
	TType -> cont 22;
	TDef -> cont 23;
	TLet -> cont 24;
	TIn -> cont 25;
	TAs -> cont 26;
	TUnit -> cont 27;
	TFst -> cont 28;
	TSnd -> cont 29;
	_ -> happyError' (tk, [])
	})

happyError_ explist 30 tk = happyError' (tk, explist)
happyError_ explist _ tk = happyError' (tk, explist)

happyThen :: () => P a -> (a -> P b) -> P b
happyThen = (thenP)
happyReturn :: () => a -> P a
happyReturn = (returnP)
happyThen1 :: () => P a -> (a -> P b) -> P b
happyThen1 = happyThen
happyReturn1 :: () => a -> P a
happyReturn1 = happyReturn
happyError' :: () => ((Token), [String]) -> P a
happyError' tk = (\(tokens, explist) -> happyError) tk
parseStmt = happySomeParser where
 happySomeParser = happyThen (happyParse action_0) (\x -> case x of {HappyAbsSyn6 z -> happyReturn z; _other -> notHappyAtAll })

parseStmts = happySomeParser where
 happySomeParser = happyThen (happyParse action_1) (\x -> case x of {HappyAbsSyn12 z -> happyReturn z; _other -> notHappyAtAll })

term = happySomeParser where
 happySomeParser = happyThen (happyParse action_2) (\x -> case x of {HappyAbsSyn8 z -> happyReturn z; _other -> notHappyAtAll })

happySeq = happyDontSeq


data ParseResult a = Ok a | Failed String
                     deriving Show
type LineNumber = Int
type P a = String -> LineNumber -> ParseResult a

getLineNo :: P LineNumber
getLineNo = \s l -> Ok l

thenP :: P a -> (a -> P b) -> P b
m `thenP` k = \s l-> case m s l of
                         Ok a     -> k a s l
                         Failed e -> Failed e

returnP :: a -> P a
returnP a = \s l-> Ok a

failP :: String -> P a
failP err = \s l -> Failed err

catchP :: P a -> (String -> P a) -> P a
catchP m k = \s l -> case m s l of
                        Ok a     -> Ok a
                        Failed e -> k e s l

happyError :: P a
happyError = \ s i -> Failed $ "Línea "++(show (i::LineNumber))++": Error de parseo\n"++(s)

data Token = TVar String
               | TType
               | TDef
               | TAbs
               | TDot
               | TOpen
               | TClose
               | TColon
               | TArrow
               | TComma
               | TEquals
               | TEOF
               | TLet
               | TIn
               | TAs
               | TUnit
               | TFst
               | TSnd
               deriving Show

----------------------------------
lexer cont s = case s of
                    [] -> cont TEOF []
                    ('\n':s)  ->  \line -> lexer cont s (line + 1)
                    (c:cs)
                          | isSpace c -> lexer cont cs
                          | isAlpha c -> lexVar (c:cs)
                    ('-':('-':cs)) -> lexer cont $ dropWhile ((/=) '\n') cs
                    ('{':('-':cs)) -> consumirBK 0 0 cont cs
                    ('-':('}':cs)) -> \ line -> Failed $ "Línea "++(show line)++": Comentario no abierto"
                    ('-':('>':cs)) -> cont TArrow cs
                    ('\\':cs)-> cont TAbs cs
                    ('.':cs) -> cont TDot cs
                    ('(':cs) -> cont TOpen cs
                    ('-':('>':cs)) -> cont TArrow cs
                    (')':cs) -> cont TClose cs
                    (':':cs) -> cont TColon cs
                    ('=':cs) -> cont TEquals cs
                    (',':cs) -> cont TComma cs
                    unknown -> \line -> Failed $ "Línea "++(show line)++": No se puede reconocer "++(show $ take 10 unknown)++ "..."
                    where lexVar cs = case span isAlpha cs of
                                           ("B",rest)    -> cont TType rest
                                           ("def",rest)  -> cont TDef rest
                                           ("let",rest)  -> cont TLet rest
                                           ("in",rest)   -> cont TIn rest
                                           ("as",rest)   -> cont TAs rest
                                           ("unit",rest) -> cont TUnit rest
                                           ("fst",rest)  -> cont TFst rest
                                           ("snd",rest)  -> cont TSnd rest
                                           (var,rest)    -> cont (TVar var) rest
                          consumirBK anidado cl cont s = case s of
                                                                      ('-':('-':cs)) -> consumirBK anidado cl cont $ dropWhile ((/=) '\n') cs
                                                                      ('{':('-':cs)) -> consumirBK (anidado+1) cl cont cs
                                                                      ('-':('}':cs)) -> case anidado of
                                                                                             0 -> \line -> lexer cont cs (line+cl)
                                                                                             _ -> consumirBK (anidado-1) cl cont cs
                                                                      ('\n':cs) -> consumirBK anidado (cl+1) cont cs
                                                                      (_:cs) -> consumirBK anidado cl cont cs

stmts_parse s = parseStmts s 1
stmt_parse s = parseStmt s 1
term_parse s = term s 1
{-# LINE 1 "templates/GenericTemplate.hs" #-}
{-# LINE 1 "templates/GenericTemplate.hs" #-}
{-# LINE 1 "<built-in>" #-}
{-# LINE 1 "<command-line>" #-}







# 1 "/usr/include/stdc-predef.h" 1 3 4

# 17 "/usr/include/stdc-predef.h" 3 4











































{-# LINE 7 "<command-line>" #-}
{-# LINE 1 "/usr/lib/ghc-8.6.5/include/ghcversion.h" #-}















{-# LINE 7 "<command-line>" #-}
{-# LINE 1 "/tmp/ghc668_0/ghc_2.h" #-}
































































































































































































{-# LINE 7 "<command-line>" #-}
{-# LINE 1 "templates/GenericTemplate.hs" #-}
-- Id: GenericTemplate.hs,v 1.26 2005/01/14 14:47:22 simonmar Exp 









{-# LINE 43 "templates/GenericTemplate.hs" #-}

data Happy_IntList = HappyCons Int Happy_IntList







{-# LINE 65 "templates/GenericTemplate.hs" #-}

{-# LINE 75 "templates/GenericTemplate.hs" #-}

{-# LINE 84 "templates/GenericTemplate.hs" #-}

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

{-# LINE 137 "templates/GenericTemplate.hs" #-}

{-# LINE 147 "templates/GenericTemplate.hs" #-}
indexShortOffAddr arr off = arr Happy_Data_Array.! off


{-# INLINE happyLt #-}
happyLt x y = (x < y)






readArrayBit arr bit =
    Bits.testBit (indexShortOffAddr arr (bit `div` 16)) (bit `mod` 16)






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
     = happyFail [] (1) tk st sts stk
happySpecReduce_0 nt fn j tk st@((HappyState (action))) sts stk
     = action nt j tk st ((st):(sts)) (fn `HappyStk` stk)

happySpecReduce_1 i fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happySpecReduce_1 nt fn j tk _ sts@(((st@(HappyState (action))):(_))) (v1`HappyStk`stk')
     = let r = fn v1 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happySpecReduce_2 i fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happySpecReduce_2 nt fn j tk _ ((_):(sts@(((st@(HappyState (action))):(_))))) (v1`HappyStk`v2`HappyStk`stk')
     = let r = fn v1 v2 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happySpecReduce_3 i fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happySpecReduce_3 nt fn j tk _ ((_):(((_):(sts@(((st@(HappyState (action))):(_))))))) (v1`HappyStk`v2`HappyStk`v3`HappyStk`stk')
     = let r = fn v1 v2 v3 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happyReduce k i fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happyReduce k nt fn j tk st sts stk
     = case happyDrop (k - ((1) :: Int)) sts of
         sts1@(((st1@(HappyState (action))):(_))) ->
                let r = fn stk in  -- it doesn't hurt to always seq here...
                happyDoSeq r (action nt j tk st1 sts1 r)

happyMonadReduce k nt fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happyMonadReduce k nt fn j tk st sts stk =
      case happyDrop k ((st):(sts)) of
        sts1@(((st1@(HappyState (action))):(_))) ->
          let drop_stk = happyDropStk k stk in
          happyThen1 (fn stk tk) (\r -> action nt j tk st1 sts1 (r `HappyStk` drop_stk))

happyMonad2Reduce k nt fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happyMonad2Reduce k nt fn j tk st sts stk =
      case happyDrop k ((st):(sts)) of
        sts1@(((st1@(HappyState (action))):(_))) ->
         let drop_stk = happyDropStk k stk





             _ = nt :: Int
             new_state = action

          in
          happyThen1 (fn stk tk) (\r -> happyNewToken new_state sts1 (r `HappyStk` drop_stk))

happyDrop (0) l = l
happyDrop n ((_):(t)) = happyDrop (n - ((1) :: Int)) t

happyDropStk (0) l = l
happyDropStk n (x `HappyStk` xs) = happyDropStk (n - ((1)::Int)) xs

-----------------------------------------------------------------------------
-- Moving to a new state after a reduction

{-# LINE 267 "templates/GenericTemplate.hs" #-}
happyGoto action j tk st = action j j tk (HappyState action)


-----------------------------------------------------------------------------
-- Error recovery ((1) is the error token)

-- parse error if we are in recovery and we fail again
happyFail explist (1) tk old_st _ stk@(x `HappyStk` _) =
     let i = (case x of { HappyErrorToken (i) -> i }) in
--      trace "failing" $ 
        happyError_ explist i tk

{-  We don't need state discarding for our restricted implementation of
    "error".  In fact, it can cause some bogus parses, so I've disabled it
    for now --SDM

-- discard a state
happyFail  (1) tk old_st (((HappyState (action))):(sts)) 
                                                (saved_tok `HappyStk` _ `HappyStk` stk) =
--      trace ("discarding state, depth " ++ show (length stk))  $
        action (1) (1) tk (HappyState (action)) sts ((saved_tok`HappyStk`stk))
-}

-- Enter error recovery: generate an error token,
--                       save the old token and carry on.
happyFail explist i tk (HappyState (action)) sts stk =
--      trace "entering error recovery" $
        action (1) (1) tk (HappyState (action)) sts ( (HappyErrorToken (i)) `HappyStk` stk)

-- Internal happy errors:

notHappyAtAll :: a
notHappyAtAll = error "Internal Happy error\n"

-----------------------------------------------------------------------------
-- Hack to get the typechecker to accept our action functions







-----------------------------------------------------------------------------
-- Seq-ing.  If the --strict flag is given, then Happy emits 
--      happySeq = happyDoSeq
-- otherwise it emits
--      happySeq = happyDontSeq

happyDoSeq, happyDontSeq :: a -> b -> b
happyDoSeq   a b = a `seq` b
happyDontSeq a b = b

-----------------------------------------------------------------------------
-- Don't inline any functions from the template.  GHC has a nasty habit
-- of deciding to inline happyGoto everywhere, which increases the size of
-- the generated parser quite a bit.

{-# LINE 333 "templates/GenericTemplate.hs" #-}
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
