import Text.Printf
import Control.Monad
import Control.Applicative

get :: Integral a => [a] -> a -> (Double, Double)
get (x:y:z:vx:vy:[vz]) n = (d, t)
    where a = vx^2 + vy^2 + vz^2
          b = 2 * (vx * x + vy * y + vz * z)
          c = x^2 + y^2 + z^2
          [a', b', c', n'] = map fromIntegral [a, b, c, n]
          t = fix $ t' a
          t' 0 = 0 -- when a is 0, b is also 0
          t' _ = -b' / (2*a')
          d = fix $ sqrt(a'*t^2 + b'*t + c') / n'
          fix x = max 1e-18 x -- fix: must be positive

readnum :: Read a => IO [a]
readnum = map read . words <$> getLine

main = do
    t <- readLn
    forM_ [1..t::Int] $ \i -> do
        n <- readLn
        s <- replicateM n readnum
        let (d, t) = get num $ fromIntegral n
            num = foldr (zipWith (+)) (replicate 6 0) s in
            printf "Case #%d: %.8f %.8f\n" i d t
