import Data.Array
import Text.Printf
import Control.Monad

get :: String -> String -> Int
get a b = f na nb
    where na = length a
          nb = length b
          sa = listArray (1, na) a
          sb = listArray (1, nb) b
          m = array ((0, 0), (na, nb)) [((i, j), f i j) | i <- [0..na], j <- [0..nb]]
          f i j
            | i <= 0 = 1
            | j <= 0 = 0
            | sa ! i == sb ! j = (r + m!(i-1, j-1)) `mod` 10000
            | otherwise = r
            where r = m!(i, j-1)


main = do
    n <- readLn
    forM_ [1..n::Int] $ \i -> do
        b <- getLine
        printf "Case #%d: %04d\n" i (get a b)
            where a = "welcome to code jam"
