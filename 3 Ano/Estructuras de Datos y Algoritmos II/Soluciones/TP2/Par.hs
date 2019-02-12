
module Par ((|||)) where

import Control.Parallel

infix 1 |||

(|||)   ::   a -> b -> (a,b)
a ||| b = (a,b)
