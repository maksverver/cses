CXXFLAGS=-std=c++17 -Wall -O2 -Wno-sign-compare

INTRODUCTORY_PROBLEMS=weird-algorithm missing-number repetitions increasing-array permutations number-spiral two-knights two-sets bit-strings trailing-zeros coin-piles palindrome-reorder gray-code tower-of-hanoi creating-strings apple-division chessboard-and-queens digit-queries grid-paths

TREE_ALGORITHM_PROBLEMS=tree-diameter tree-distances-1 tree-distances-2

PROBLEMS=$(INTRODUCTORY_PROBLEMS) $(TREE_ALGORITHM_PROBLEMS)

all: $(PROBLEMS)

clean:
	rm -f $(PROBLEMS)
