import Data.MemoTrie
import Text.Printf
import Control.Monad

get :: String -> String -> Int
get a b = f na nb
    where na = length a
          nb = length b
          f = memo2 f'
          f' i j
            | i <= 0 = 1
            | j <= 0 = 0
            | a !! (i-1) == b !! (j-1) = (r + f (i-1) (j-1)) `mod` 10000
            | otherwise = r
            where r = f i (j-1)


main = do
    n <- readLn
    forM_ [1..n::Int] $ \i -> do
        b <- getLine
        printf "Case #%d: %04d\n" i (get a b)
            where a = "welcome to code jam"
