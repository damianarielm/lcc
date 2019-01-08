{-# OPTIONS_GHC -w #-}
{-# LANGUAGE RankNTypes #-}

module Parser where

import Types 
import Data.Char (isAlpha, isDigit, isSpace)
import UI.NCurses (Color (..))
import qualified Data.Array as Happy_Data_Array
import qualified Data.Bits as Bits
import Control.Applicative(Applicative(..))
import Control.Monad (ap)

-- parser produced by Happy Version 1.19.9

data HappyAbsSyn 
	= HappyTerminal (Token)
	| HappyErrorToken Int
	| HappyAbsSyn4 (([State], [Rule]))
	| HappyAbsSyn5 ([State])
	| HappyAbsSyn6 (Color)
	| HappyAbsSyn7 ([Rule])
	| HappyAbsSyn8 ([Condition])
	| HappyAbsSyn9 (Char -> Int -> (Int -> Int -> Bool) -> Int -> Condition)
	| HappyAbsSyn10 (Int -> (Char -> Char -> Bool) -> Char -> Condition)
	| HappyAbsSyn11 (forall a. (Ord a) => a -> a -> Bool)

{- to allow type-synonyms as our monads (likely
 - with explicitly-specified bind and return)
 - in Haskell98, it seems that with
 - /type M a = .../, then /(HappyReduction M)/
 - is not allowed.  But Happy is a
 - code-generator that can just substitute it.
type HappyReduction m = 
	   Int 
	-> (Token)
	-> HappyState (Token) (HappyStk HappyAbsSyn -> [(Token)] -> m HappyAbsSyn)
	-> [HappyState (Token) (HappyStk HappyAbsSyn -> [(Token)] -> m HappyAbsSyn)] 
	-> HappyStk HappyAbsSyn 
	-> [(Token)] -> m HappyAbsSyn
-}

action_0,
 action_1,
 action_2,
 action_3,
 action_4,
 action_5,
 action_6,
 action_7,
 action_8,
 action_9,
 action_10,
 action_11,
 action_12,
 action_13,
 action_14,
 action_15,
 action_16,
 action_17,
 action_18,
 action_19,
 action_20,
 action_21,
 action_22,
 action_23,
 action_24,
 action_25,
 action_26,
 action_27,
 action_28,
 action_29,
 action_30,
 action_31,
 action_32,
 action_33,
 action_34,
 action_35,
 action_36,
 action_37,
 action_38,
 action_39,
 action_40,
 action_41,
 action_42,
 action_43,
 action_44,
 action_45,
 action_46,
 action_47,
 action_48,
 action_49,
 action_50,
 action_51,
 action_52,
 action_53,
 action_54,
 action_55,
 action_56,
 action_57,
 action_58,
 action_59,
 action_60,
 action_61,
 action_62,
 action_63,
 action_64,
 action_65,
 action_66,
 action_67,
 action_68,
 action_69,
 action_70,
 action_71,
 action_72,
 action_73,
 action_74,
 action_75 :: () => Int -> ({-HappyReduction (HappyIdentity) = -}
	   Int 
	-> (Token)
	-> HappyState (Token) (HappyStk HappyAbsSyn -> [(Token)] -> (HappyIdentity) HappyAbsSyn)
	-> [HappyState (Token) (HappyStk HappyAbsSyn -> [(Token)] -> (HappyIdentity) HappyAbsSyn)] 
	-> HappyStk HappyAbsSyn 
	-> [(Token)] -> (HappyIdentity) HappyAbsSyn)

happyReduce_1,
 happyReduce_2,
 happyReduce_3,
 happyReduce_4,
 happyReduce_5,
 happyReduce_6,
 happyReduce_7,
 happyReduce_8,
 happyReduce_9,
 happyReduce_10,
 happyReduce_11,
 happyReduce_12,
 happyReduce_13,
 happyReduce_14,
 happyReduce_15,
 happyReduce_16,
 happyReduce_17,
 happyReduce_18,
 happyReduce_19,
 happyReduce_20,
 happyReduce_21,
 happyReduce_22,
 happyReduce_23,
 happyReduce_24,
 happyReduce_25,
 happyReduce_26,
 happyReduce_27,
 happyReduce_28,
 happyReduce_29,
 happyReduce_30,
 happyReduce_31,
 happyReduce_32,
 happyReduce_33 :: () => ({-HappyReduction (HappyIdentity) = -}
	   Int 
	-> (Token)
	-> HappyState (Token) (HappyStk HappyAbsSyn -> [(Token)] -> (HappyIdentity) HappyAbsSyn)
	-> [HappyState (Token) (HappyStk HappyAbsSyn -> [(Token)] -> (HappyIdentity) HappyAbsSyn)] 
	-> HappyStk HappyAbsSyn 
	-> [(Token)] -> (HappyIdentity) HappyAbsSyn)

happyExpList :: Happy_Data_Array.Array Int Int
happyExpList = Happy_Data_Array.listArray (0,112) ([0,256,0,0,32,0,128,0,0,0,8,0,0,0,0,512,0,0,0,0,0,256,0,0,1,0,2048,0,0,1024,0,0,2048,0,0,16,0,0,32,0,16384,0,0,0,64,0,64,0,0,32,0,96,49152,63,8160,0,0,1020,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,32768,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,1024,0,0,2048,0,0,16,0,0,16,0,16384,0,0,2048,0,0,0,0,0,512,0,0,16,0,16,0,0,4096,0,16384,0,0,0,0,0,0,16128,0,0,1,0,4096,0,0,1024,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,0,4,0,16384,0,0,512,0,0,0,2,0,16128,0,0,8,0,0,0,0,0,32,0,0,0,0
	])

{-# NOINLINE happyExpListPerState #-}
happyExpListPerState st =
    token_strs_expected
  where token_strs = ["error","%dummy","%start_parse","Automata","States","Color","Rules","Comparsion","Distance","Cardinal","Cmp","Chebyshev","Manhattan","State","Black","Red","Green","Yellow","Blue","Magenta","Cyan","White","':'","','","'\\''","'('","')'","Int","Char","Eq","Neq","Leq","Geq","Lower","Greater","And","North","South","East","West","NW","NE","SE","SW","%eof"]
        bit_start = st * 45
        bit_end = (st + 1) * 45
        read_bit = readArrayBit happyExpList
        bits = map read_bit [bit_start..bit_end - 1]
        bits_indexed = zip bits [0..44]
        token_strs_expected = concatMap f bits_indexed
        f (False, _) = []
        f (True, nr) = [token_strs !! nr]

action_0 (25) = happyShift action_3
action_0 (4) = happyGoto action_4
action_0 (5) = happyGoto action_2
action_0 _ = happyReduce_3

action_1 (25) = happyShift action_3
action_1 (5) = happyGoto action_2
action_1 _ = happyFail (happyExpListPerState 1)

action_2 (14) = happyShift action_7
action_2 (7) = happyGoto action_6
action_2 _ = happyReduce_14

action_3 (29) = happyShift action_5
action_3 _ = happyFail (happyExpListPerState 3)

action_4 (45) = happyAccept
action_4 _ = happyFail (happyExpListPerState 4)

action_5 (25) = happyShift action_9
action_5 _ = happyFail (happyExpListPerState 5)

action_6 _ = happyReduce_1

action_7 (30) = happyShift action_8
action_7 _ = happyFail (happyExpListPerState 7)

action_8 (25) = happyShift action_11
action_8 _ = happyFail (happyExpListPerState 8)

action_9 (23) = happyShift action_10
action_9 _ = happyFail (happyExpListPerState 9)

action_10 (25) = happyShift action_13
action_10 _ = happyFail (happyExpListPerState 10)

action_11 (29) = happyShift action_12
action_11 _ = happyFail (happyExpListPerState 11)

action_12 (25) = happyShift action_15
action_12 _ = happyFail (happyExpListPerState 12)

action_13 (29) = happyShift action_14
action_13 _ = happyFail (happyExpListPerState 13)

action_14 (25) = happyShift action_19
action_14 _ = happyFail (happyExpListPerState 14)

action_15 (23) = happyShift action_17
action_15 (36) = happyShift action_18
action_15 (8) = happyGoto action_16
action_15 _ = happyFail (happyExpListPerState 15)

action_16 (23) = happyShift action_42
action_16 _ = happyFail (happyExpListPerState 16)

action_17 (25) = happyShift action_41
action_17 _ = happyFail (happyExpListPerState 17)

action_18 (12) = happyShift action_31
action_18 (13) = happyShift action_32
action_18 (37) = happyShift action_33
action_18 (38) = happyShift action_34
action_18 (39) = happyShift action_35
action_18 (40) = happyShift action_36
action_18 (41) = happyShift action_37
action_18 (42) = happyShift action_38
action_18 (43) = happyShift action_39
action_18 (44) = happyShift action_40
action_18 (9) = happyGoto action_29
action_18 (10) = happyGoto action_30
action_18 _ = happyFail (happyExpListPerState 18)

action_19 (15) = happyShift action_21
action_19 (16) = happyShift action_22
action_19 (17) = happyShift action_23
action_19 (18) = happyShift action_24
action_19 (19) = happyShift action_25
action_19 (20) = happyShift action_26
action_19 (21) = happyShift action_27
action_19 (22) = happyShift action_28
action_19 (6) = happyGoto action_20
action_19 _ = happyFail (happyExpListPerState 19)

action_20 (15) = happyShift action_21
action_20 (16) = happyShift action_22
action_20 (17) = happyShift action_23
action_20 (18) = happyShift action_24
action_20 (19) = happyShift action_25
action_20 (20) = happyShift action_26
action_20 (21) = happyShift action_27
action_20 (22) = happyShift action_28
action_20 (6) = happyGoto action_47
action_20 _ = happyFail (happyExpListPerState 20)

action_21 _ = happyReduce_4

action_22 _ = happyReduce_5

action_23 _ = happyReduce_6

action_24 _ = happyReduce_7

action_25 _ = happyReduce_8

action_26 _ = happyReduce_9

action_27 _ = happyReduce_10

action_28 _ = happyReduce_11

action_29 (26) = happyShift action_46
action_29 _ = happyFail (happyExpListPerState 29)

action_30 (26) = happyShift action_45
action_30 _ = happyFail (happyExpListPerState 30)

action_31 _ = happyReduce_18

action_32 _ = happyReduce_19

action_33 _ = happyReduce_20

action_34 _ = happyReduce_21

action_35 _ = happyReduce_22

action_36 _ = happyReduce_23

action_37 _ = happyReduce_25

action_38 _ = happyReduce_24

action_39 _ = happyReduce_26

action_40 _ = happyReduce_27

action_41 (29) = happyShift action_44
action_41 _ = happyFail (happyExpListPerState 41)

action_42 (25) = happyShift action_43
action_42 _ = happyFail (happyExpListPerState 42)

action_43 (29) = happyShift action_52
action_43 _ = happyFail (happyExpListPerState 43)

action_44 (25) = happyShift action_51
action_44 _ = happyFail (happyExpListPerState 44)

action_45 (28) = happyShift action_50
action_45 _ = happyFail (happyExpListPerState 45)

action_46 (25) = happyShift action_49
action_46 _ = happyFail (happyExpListPerState 46)

action_47 (25) = happyShift action_3
action_47 (5) = happyGoto action_48
action_47 _ = happyReduce_3

action_48 _ = happyReduce_2

action_49 (29) = happyShift action_56
action_49 _ = happyFail (happyExpListPerState 49)

action_50 (27) = happyShift action_55
action_50 _ = happyFail (happyExpListPerState 50)

action_51 (14) = happyShift action_7
action_51 (7) = happyGoto action_54
action_51 _ = happyReduce_14

action_52 (25) = happyShift action_53
action_52 _ = happyFail (happyExpListPerState 52)

action_53 (14) = happyShift action_7
action_53 (7) = happyGoto action_65
action_53 _ = happyReduce_14

action_54 _ = happyReduce_12

action_55 (30) = happyShift action_59
action_55 (31) = happyShift action_60
action_55 (32) = happyShift action_61
action_55 (33) = happyShift action_62
action_55 (34) = happyShift action_63
action_55 (35) = happyShift action_64
action_55 (11) = happyGoto action_58
action_55 _ = happyFail (happyExpListPerState 55)

action_56 (25) = happyShift action_57
action_56 _ = happyFail (happyExpListPerState 56)

action_57 (24) = happyShift action_67
action_57 _ = happyFail (happyExpListPerState 57)

action_58 (25) = happyShift action_66
action_58 _ = happyFail (happyExpListPerState 58)

action_59 _ = happyReduce_28

action_60 _ = happyReduce_33

action_61 _ = happyReduce_29

action_62 _ = happyReduce_30

action_63 _ = happyReduce_31

action_64 _ = happyReduce_32

action_65 _ = happyReduce_13

action_66 (29) = happyShift action_69
action_66 _ = happyFail (happyExpListPerState 66)

action_67 (28) = happyShift action_68
action_67 _ = happyFail (happyExpListPerState 67)

action_68 (27) = happyShift action_71
action_68 _ = happyFail (happyExpListPerState 68)

action_69 (25) = happyShift action_70
action_69 _ = happyFail (happyExpListPerState 69)

action_70 (36) = happyShift action_18
action_70 (8) = happyGoto action_73
action_70 _ = happyReduce_17

action_71 (30) = happyShift action_59
action_71 (31) = happyShift action_60
action_71 (32) = happyShift action_61
action_71 (33) = happyShift action_62
action_71 (34) = happyShift action_63
action_71 (35) = happyShift action_64
action_71 (11) = happyGoto action_72
action_71 _ = happyFail (happyExpListPerState 71)

action_72 (28) = happyShift action_74
action_72 _ = happyFail (happyExpListPerState 72)

action_73 _ = happyReduce_16

action_74 (36) = happyShift action_18
action_74 (8) = happyGoto action_75
action_74 _ = happyReduce_17

action_75 _ = happyReduce_15

happyReduce_1 = happySpecReduce_2  4 happyReduction_1
happyReduction_1 (HappyAbsSyn7  happy_var_2)
	(HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn4
		 ((happy_var_1, happy_var_2)
	)
happyReduction_1 _ _  = notHappyAtAll 

happyReduce_2 = happyReduce 10 5 happyReduction_2
happyReduction_2 ((HappyAbsSyn5  happy_var_10) `HappyStk`
	(HappyAbsSyn6  happy_var_9) `HappyStk`
	(HappyAbsSyn6  happy_var_8) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TChar happy_var_6)) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TChar happy_var_2)) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn5
		 ((happy_var_2, happy_var_6, happy_var_8, happy_var_9) : happy_var_10
	) `HappyStk` happyRest

happyReduce_3 = happySpecReduce_0  5 happyReduction_3
happyReduction_3  =  HappyAbsSyn5
		 ([]
	)

happyReduce_4 = happySpecReduce_1  6 happyReduction_4
happyReduction_4 _
	 =  HappyAbsSyn6
		 (ColorBlack
	)

happyReduce_5 = happySpecReduce_1  6 happyReduction_5
happyReduction_5 _
	 =  HappyAbsSyn6
		 (ColorRed
	)

happyReduce_6 = happySpecReduce_1  6 happyReduction_6
happyReduction_6 _
	 =  HappyAbsSyn6
		 (ColorGreen
	)

happyReduce_7 = happySpecReduce_1  6 happyReduction_7
happyReduction_7 _
	 =  HappyAbsSyn6
		 (ColorYellow
	)

happyReduce_8 = happySpecReduce_1  6 happyReduction_8
happyReduction_8 _
	 =  HappyAbsSyn6
		 (ColorBlue
	)

happyReduce_9 = happySpecReduce_1  6 happyReduction_9
happyReduction_9 _
	 =  HappyAbsSyn6
		 (ColorMagenta
	)

happyReduce_10 = happySpecReduce_1  6 happyReduction_10
happyReduction_10 _
	 =  HappyAbsSyn6
		 (ColorCyan
	)

happyReduce_11 = happySpecReduce_1  6 happyReduction_11
happyReduction_11 _
	 =  HappyAbsSyn6
		 (ColorWhite
	)

happyReduce_12 = happyReduce 10 7 happyReduction_12
happyReduction_12 ((HappyAbsSyn7  happy_var_10) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TChar happy_var_8)) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TChar happy_var_4)) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn7
		 ((happy_var_4,[], happy_var_8) : happy_var_10
	) `HappyStk` happyRest

happyReduce_13 = happyReduce 11 7 happyReduction_13
happyReduction_13 ((HappyAbsSyn7  happy_var_11) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TChar happy_var_9)) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn8  happy_var_6) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TChar happy_var_4)) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn7
		 ((happy_var_4, happy_var_6, happy_var_9) : happy_var_11
	) `HappyStk` happyRest

happyReduce_14 = happySpecReduce_0  7 happyReduction_14
happyReduction_14  =  HappyAbsSyn7
		 ([]
	)

happyReduce_15 = happyReduce 12 8 happyReduction_15
happyReduction_15 ((HappyAbsSyn8  happy_var_12) `HappyStk`
	(HappyTerminal (TInt happy_var_11)) `HappyStk`
	(HappyAbsSyn11  happy_var_10) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TInt happy_var_8)) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TChar happy_var_5)) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn9  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn8
		 ((happy_var_2 happy_var_5 happy_var_8 happy_var_10 happy_var_11) : happy_var_12
	) `HappyStk` happyRest

happyReduce_16 = happyReduce 10 8 happyReduction_16
happyReduction_16 ((HappyAbsSyn8  happy_var_10) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TChar happy_var_8)) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn11  happy_var_6) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TInt happy_var_4)) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn10  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn8
		 ((happy_var_2 happy_var_4 happy_var_6 happy_var_8) : happy_var_10
	) `HappyStk` happyRest

happyReduce_17 = happySpecReduce_0  8 happyReduction_17
happyReduction_17  =  HappyAbsSyn8
		 ([]
	)

happyReduce_18 = happySpecReduce_1  9 happyReduction_18
happyReduction_18 _
	 =  HappyAbsSyn9
		 (Chebyshev
	)

happyReduce_19 = happySpecReduce_1  9 happyReduction_19
happyReduction_19 _
	 =  HappyAbsSyn9
		 (Manhattan
	)

happyReduce_20 = happySpecReduce_1  10 happyReduction_20
happyReduction_20 _
	 =  HappyAbsSyn10
		 (North
	)

happyReduce_21 = happySpecReduce_1  10 happyReduction_21
happyReduction_21 _
	 =  HappyAbsSyn10
		 (South
	)

happyReduce_22 = happySpecReduce_1  10 happyReduction_22
happyReduction_22 _
	 =  HappyAbsSyn10
		 (East
	)

happyReduce_23 = happySpecReduce_1  10 happyReduction_23
happyReduction_23 _
	 =  HappyAbsSyn10
		 (West
	)

happyReduce_24 = happySpecReduce_1  10 happyReduction_24
happyReduction_24 _
	 =  HappyAbsSyn10
		 (NE
	)

happyReduce_25 = happySpecReduce_1  10 happyReduction_25
happyReduction_25 _
	 =  HappyAbsSyn10
		 (NW
	)

happyReduce_26 = happySpecReduce_1  10 happyReduction_26
happyReduction_26 _
	 =  HappyAbsSyn10
		 (SE
	)

happyReduce_27 = happySpecReduce_1  10 happyReduction_27
happyReduction_27 _
	 =  HappyAbsSyn10
		 (SW
	)

happyReduce_28 = happySpecReduce_1  11 happyReduction_28
happyReduction_28 _
	 =  HappyAbsSyn11
		 ((==)
	)

happyReduce_29 = happySpecReduce_1  11 happyReduction_29
happyReduction_29 _
	 =  HappyAbsSyn11
		 ((<=)
	)

happyReduce_30 = happySpecReduce_1  11 happyReduction_30
happyReduction_30 _
	 =  HappyAbsSyn11
		 ((>=)
	)

happyReduce_31 = happySpecReduce_1  11 happyReduction_31
happyReduction_31 _
	 =  HappyAbsSyn11
		 ((<)
	)

happyReduce_32 = happySpecReduce_1  11 happyReduction_32
happyReduction_32 _
	 =  HappyAbsSyn11
		 ((>)
	)

happyReduce_33 = happySpecReduce_1  11 happyReduction_33
happyReduction_33 _
	 =  HappyAbsSyn11
		 ((/=)
	)

happyNewToken action sts stk [] =
	action 45 45 notHappyAtAll (HappyState action) sts stk []

happyNewToken action sts stk (tk:tks) =
	let cont i = action i i tk (HappyState action) sts stk tks in
	case tk of {
	TChebyshev -> cont 12;
	TManhattan -> cont 13;
	TState -> cont 14;
	TBlack -> cont 15;
	TRed -> cont 16;
	TGreen -> cont 17;
	TYellow -> cont 18;
	TBlue -> cont 19;
	TMagenta -> cont 20;
	TCyan -> cont 21;
	TWhite -> cont 22;
	TColon -> cont 23;
	TSemiColon -> cont 24;
	TApostrophe -> cont 25;
	TPOpen -> cont 26;
	TPClose -> cont 27;
	TInt happy_dollar_dollar -> cont 28;
	TChar happy_dollar_dollar -> cont 29;
	TEq -> cont 30;
	TNeq -> cont 31;
	TLeq -> cont 32;
	TGeq -> cont 33;
	TLower -> cont 34;
	TGreater -> cont 35;
	TAnd -> cont 36;
	TNorth -> cont 37;
	TSouth -> cont 38;
	TEast -> cont 39;
	TWest -> cont 40;
	TNW -> cont 41;
	TNE -> cont 42;
	TSE -> cont 43;
	TSW -> cont 44;
	_ -> happyError' ((tk:tks), [])
	}

happyError_ explist 45 tk tks = happyError' (tks, explist)
happyError_ explist _ tk tks = happyError' ((tk:tks), explist)

newtype HappyIdentity a = HappyIdentity a
happyIdentity = HappyIdentity
happyRunIdentity (HappyIdentity a) = a

instance Functor HappyIdentity where
    fmap f (HappyIdentity a) = HappyIdentity (f a)

instance Applicative HappyIdentity where
    pure  = HappyIdentity
    (<*>) = ap
instance Monad HappyIdentity where
    return = pure
    (HappyIdentity p) >>= q = q p

happyThen :: () => HappyIdentity a -> (a -> HappyIdentity b) -> HappyIdentity b
happyThen = (>>=)
happyReturn :: () => a -> HappyIdentity a
happyReturn = (return)
happyThen1 m k tks = (>>=) m (\a -> k a tks)
happyReturn1 :: () => a -> b -> HappyIdentity a
happyReturn1 = \a tks -> (return) a
happyError' :: () => ([(Token)], [String]) -> HappyIdentity a
happyError' = HappyIdentity . (\(tokens, _) -> error "Error de parseo en automata" tokens)
parse tks = happyRunIdentity happySomeParser where
 happySomeParser = happyThen (happyParse action_0 tks) (\x -> case x of {HappyAbsSyn4 z -> happyReturn z; _other -> notHappyAtAll })

happySeq = happyDontSeq


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
{-# LINE 1 "templates/GenericTemplate.hs" #-}
{-# LINE 1 "templates/GenericTemplate.hs" #-}
{-# LINE 1 "<built-in>" #-}
{-# LINE 1 "<command-line>" #-}







# 1 "/usr/include/stdc-predef.h" 1 3 4

# 17 "/usr/include/stdc-predef.h" 3 4














































{-# LINE 7 "<command-line>" #-}
{-# LINE 1 "/usr/lib/ghc/include/ghcversion.h" #-}















{-# LINE 7 "<command-line>" #-}
{-# LINE 1 "/tmp/ghc8814_0/ghc_2.h" #-}








































































































































































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
