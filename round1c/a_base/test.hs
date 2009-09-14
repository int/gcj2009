import Text.Printf
import Control.Monad
import Data.Map

get :: String -> Integer -- Use Integer instead of Int to avoid overflow
get str = g $ foldl f empty str
    where f m x
            | x `member` m = m
            | s == 0 = insert x 1 m -- first
            | s == 1 = insert x 0 m -- second
            | otherwise = insert x s m -- others
            where s = size' m
          g m = foldl (\x y -> x*b + m!y) 0 str
            where b = max 2 $ size' m
          size' = toInteger . size -- make it Integer

main = do
    t <- readLn
    forM_ [1..t::Int] $ \i -> do
        printf "Case #%d: %d\n" i . get =<< getLine
