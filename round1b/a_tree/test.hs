import Data.Set
import Control.Monad
import Text.Printf
import Text.ParserCombinators.Parsec
import Text.ParserCombinators.Parsec.Token
import Text.ParserCombinators.Parsec.Language

data Tree = Leaf Double | Node Double String Tree Tree

get :: Set String -> Tree -> Double -> Double
get s (Leaf d) p = p * d
get s (Node d str a b) p = if member str s then get s a p' else get s b p'
    where p' = p * d

word = many1 letter
lexer = makeTokenParser emptyDef
pare = parens lexer
double = float lexer

tree = pare t
    where t = do {spaces; d <- double; spaces; r <- left d; spaces; return r}
          
left d = do {s <- word; spaces; a <- tree; spaces; b <- tree; return (Node d s a b)}
    <|> return (Leaf d)

right (Right x) = x

main = do
    n <- readLn
    forM_ [1..n::Int] $ \i -> do
        printf "Case #%d:\n" i
        l <- readLn
        strs <- replicateM l getLine
        let t = right $ parse tree "" (unlines strs)
        a <- readLn
        forM_ [1..a::Int] $ \_ -> do
            line <- getLine
            printf "%.8f\n" $ get (fromList . drop 2 . words $ line) t 1
