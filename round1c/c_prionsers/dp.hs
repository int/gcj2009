-- ghc --make -O2 -threaded dp
import Data.Array.IO
import Control.Monad
import Control.Applicative
import Text.Printf

get :: [Int] -> Int -> IO Int
get id q = do
    m <- newArray ((0, 0), (q, q)) 0
    sequence_ [ f m i j | len <- [2..q+1], i <- [0..q], let j = i+len-1, j <= q]
    readArray m (0, q)
    where f :: IOArray (Int,Int) Int -> Int -> Int -> IO ()
          f m i j = writeArray m (i, j) =<< minimum <$> mapM g [i..j-1]
            where g k = do
                    a <- readArray m (i, k)
                    b <- readArray m (k+1, j)
                    return $ a + b + id!!(j+1) - id!!i - 2

readints :: IO [Int]
readints = map read . words <$> getLine 

main = do
    n <- readLn
    forM_ [1..n::Int] $ \i -> do
        [p, q] <- readints
        id <- readints
        printf "Case #%d: %d\n" i =<< get ([0] ++ id ++ [p + 1]) q
