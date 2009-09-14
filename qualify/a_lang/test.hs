import Text.Printf
import Text.Regex.PCRE
import Control.Monad

get p = length . filter (=~ p)
reg p = "^" ++ map (\x -> case x of '(' -> '['; ')' -> ']'; _ -> x) p ++ "$"

main = do
    line <- getLine
    let [l, d, n] = map read $ words line :: [Int]
    dict <- replicateM d getLine
    forM_ [1..n] $ \i -> do
        p <- getLine
        printf "Case #%d: %d\n" i (get (reg p) dict)
