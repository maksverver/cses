-- Range Queries and Copies
-- https://cses.fi/problemset/task/1737/

import Control.Monad
import Data.Functor
import Data.Sequence

data SegmentTree
    = Branch Int Int SegmentTree SegmentTree  -- size value left right
    | Leaf Int  -- value
    deriving (Show)

stSize :: SegmentTree -> Int
stSize (Branch size _ _ _) = size
stSize (Leaf _)            = 1

stValue :: SegmentTree -> Int
stValue (Branch _ value _ _) = value
stValue (Leaf value) = value

stBranch :: SegmentTree -> SegmentTree -> SegmentTree
stBranch l r = Branch (stSize l + stSize r) (stValue l + stValue r) l r

stConstruct :: [Int] -> SegmentTree
stConstruct a = combineAll (map Leaf a)
  where
    combineAll :: [SegmentTree] -> SegmentTree
    combineAll [] = error "cannot construct an empty segment tree"
    combineAll [root] = root
    combineAll nodes = combineAll (addLayer nodes)

    addLayer :: [SegmentTree] -> [SegmentTree]
    addLayer [] = []
    addLayer [x] = [x]
    addLayer (l:r:rest) = stBranch l r:addLayer rest

stAssign :: Int -> Int -> SegmentTree -> SegmentTree
stAssign 0 v (Leaf _) = Leaf v
stAssign i v (Branch s _ l r) = stBranch l' r'
  where
    (l', r')
      | i < stSize l = (stAssign i v l, r)
      | otherwise    = (l, stAssign (i - stSize l) v r)

stGetRange :: SegmentTree -> Int -> Int -> Int
stGetRange tree a b
  | b <= 0 || a >= stSize tree = 0
  | a <= 0 && b >= stSize tree = stValue tree
  | otherwise = stGetRange l a b + stGetRange r (a - stSize l) (b - stSize l)
  where Branch s v l r = tree

main = do
  [n, q] <- readInts
  a <- readInts
  let state = singleton $ stConstruct a
  foldM_ processQuery state [1..q]

  where
    readInts :: IO [Int]
    readInts = getLine <&> map read . words

    processQuery :: Seq SegmentTree -> Int -> IO (Seq SegmentTree)
    processQuery state _ = readInts >>= query
      where
        query [1, i, a, x] = do
          --print $ "setting " ++ (show i) ++ " " ++ (show a) ++ " " ++ (show x)
          return $ adjust' (stAssign (a - 1) x) (i - 1) state

        query [2, i, a, b] = do
          --print $ "querying " ++ (show i) ++ " " ++ (show a) ++ " " ++ (show b)
          print $ stGetRange (index state (i - 1)) (a - 1) b
          return state

        query [3, i] = do
          --print $ "copying " ++ show i
          return $ state |> index state (i - 1)
