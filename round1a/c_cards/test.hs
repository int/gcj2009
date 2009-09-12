import Data.MemoTrie
import Text.Printf
import Control.Monad

bino :: Int -> Int -> Double
bino = memo2 c
    where c n k
            | n < 0 || k > n = 0
            | k == 0 || k == n = 1
            | otherwise = bino (n-1) (k-1) + bino (n-1) k

get :: Int -> Int -> Double
get c n = f 0
    where f = memo f'
          f' k = if k == c then 0 else (1 + e) / (1 - q)
            where e = sum [ bino (c-k) x * bino k (n-x) * p * f (k+x) | x <- [1..n], k + x <= c]
                  p = 1 / bino c n
                  q = bino k n * p

main = do
    t <- readLn
    forM_ [1..t::Int] $ \i -> do
        line <- getLine
        let [c, n] = map read . words $ line
        printf "Case #%d: %.8f\n" i (get c n)
