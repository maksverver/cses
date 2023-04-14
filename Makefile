CXXFLAGS=-std=c++20 -Wall -Og -Wno-sign-compare

INTRODUCTORY_PROBLEMS=weird-algorithm missing-number repetitions increasing-array permutations number-spiral two-knights two-sets bit-strings trailing-zeros coin-piles palindrome-reorder gray-code tower-of-hanoi creating-strings apple-division chessboard-and-queens digit-queries grid-paths

TREE_ALGORITHM_PROBLEMS=tree-diameter tree-distances-I tree-distances-II

SORTING_AND_SEARCHING_PROBLEMS=distinct-numbers apartments ferris-wheel concert-tickets concert-tickets-2 restaurant-customers movie-festival movie-festival-2-too-complicated sum-of-two-values maximum-subarray-sum stick-lengths missing-coin-sum collecting-numbers collecting-numbers-II playlist towers traffic-lights josephus-problem-I josephus-problem-II nested-ranges-check nested-ranges-count nested-ranges-count-2 room-allocation factory-machines tasks-and-deadlines reading-books sum-of-three-values sum-of-four-values nearest-smaller-values subarray-sums-I subarray-sums-II

PROBLEMS=$(INTRODUCTORY_PROBLEMS) $(TREE_ALGORITHM_PROBLEMS) $(SORTING_AND_SEARCHING_PROBLEMS)

all: $(PROBLEMS)

clean:
	rm -f $(PROBLEMS)
