CXXFLAGS=-std=c++17 -Wall -Og -Wno-sign-compare
PROBLEMS=weird-algorithm missing-number repetitions increasing-array permutations number-spiral two-knights two-sets bit-strings trailing-zeros coin-piles palindrome-reorder gray-code tower-of-hanoi creating-strings tree-diameter tree-distances-1 tree-distances-2

all: $(PROBLEMS)

clean:
	rm -f $(PROBLEMS)
