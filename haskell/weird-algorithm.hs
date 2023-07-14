-- Weird Algorithm
-- https://cses.fi/problemset/task/1068

collatz :: Integer -> [Integer]
collatz 1 = [1]
collatz n = n:collatz (if even n then n `div` 2 else 3 * n + 1)

main = getLine >>= (putStrLn . unwords . map show . collatz . read)
