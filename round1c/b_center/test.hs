import Text.Printf
import Control.Monad
import Control.Applicative

get :: [Double] -> Int -> (Double, Double)
get (x:y:z:vx:vy:[vz]) n = g . fix $ f a b c
    where a = vx^2 + vy^2 + vz^2
          b = 2 * (vx * x + vy * y + vz * z)
          c = x^2 + y^2 + z^2
          f 0 b c = if b < 0 then (0, -c / b) else (c, 0)
          f a b c = (d, t)
            where d = a*t^2 + b*t + c
                  t = -b / (2*a)
          fix (d, t)
              | t < 0 = (c, 0)
              | d < 0 = (0, t)
              | otherwise = (d, t)
          g (d, t) = (sqrt d / fromIntegral n, t)

readnum :: IO [Double]
readnum = map read . words <$> getLine 

main = do
    t <- readLn
    forM_ [1..t::Int] $ \i -> do
        n <- readLn
        s <- replicateM n readnum
        let (d, t) = get num $ fromIntegral n
            num = foldr (zipWith (+)) (replicate 6 0) s in
            printf "Case #%d: %.8f %.8f\n" i d (t + 1e-18) -- avoid -0.00000000
