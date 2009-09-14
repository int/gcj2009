import Data.Array
import Data.MemoTrie
import Control.Monad
import Control.Applicative
import Text.Printf

get :: [Int] -> Int -> Int
get id = f 0
    where f = memo2 f'
          f' i j
            | i == j = 0
            | otherwise = minimum [f i k + f (k+1) j + a!(j+1) - a!i - 2 | k <- [i..j-1]]
            where a = listArray (0, length id - 1) id

readints :: IO [Int]
readints = map read . words <$> getLine 

main = do
    n <- readLn
    forM_ [1..n::Int] $ \i -> do
        [p, q] <- readints
        id <- readints
        printf "Case #%d: %d\n" i $ get ([0] ++ id ++ [p + 1]) q

