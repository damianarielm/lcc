module Par ((|||)) where

import Control.Parallel

infixl 1 |||
(|||)   ::   a -> b -> (a,b)
a ||| b = (a,b)
