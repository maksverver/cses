INTRODUCTORY_PROBLEMS=weird-algorithm missing-number repetitions increasing-array permutations number-spiral two-knights two-sets bit-strings trailing-zeros coin-piles palindrome-reorder gray-code tower-of-hanoi creating-strings apple-division chessboard-and-queens digit-queries grid-paths

TREE_ALGORITHM_PROBLEMS=tree-diameter tree-distances-I tree-distances-II

SORTING_AND_SEARCHING_PROBLEMS=distinct-numbers apartments ferris-wheel concert-tickets concert-tickets-2 restaurant-customers movie-festival movie-festival-2-too-complicated sum-of-two-values maximum-subarray-sum maximum-subarray-sum-2-too-complicated maximum-subarray-sum-3 stick-lengths missing-coin-sum collecting-numbers collecting-numbers-II playlist towers traffic-lights josephus-problem-I josephus-problem-II nested-ranges-check nested-ranges-count nested-ranges-count-2 room-allocation factory-machines tasks-and-deadlines reading-books sum-of-three-values sum-of-four-values sum-of-four-values-2 nearest-smaller-values subarray-sums-I subarray-sums-II subarray-divisibility subarray-distinct-values array-division sliding-median sliding-cost movie-festival-II maximum-subarray-sum-II

DYNAMIC_PROGRAMMING_PROBLEMS=dice-combinations minimizing-coins coin-combinations-I coin-combinations-II removing-digits grid-paths-DP book-shop array-description counting-towers edit-distance rectangle-cutting money-sums removal-game two-sets-II increasing-subsequence projects elevator-rides elevator-rides-2 counting-tilings counting-tilings-2 counting-numbers

GRAPH_ALGORITHM_PROBLEMS=counting-rooms labyrinth building-roads message-route building-teams round-trip monsters shortest-routes-I shortest-routes-II high-score flight-discount cycle-finding flight-routes round-trip-II course-schedule longest-flight-route game-routes investigation planets-queries-I planets-queries-II planets-cycles road-reparation road-construction flight-routes-check flight-routes-check-2 planets-and-kingdoms giant-pizza coin-collector mail-delivery de-bruijn-sequence teleporters-path hamiltonian-flights knights-tour download-speed police-chase school-dance distinct-routes

RANGE_QUERY_PROBLEMS=static-range-sum-queries static-range-minimum-queries dynamic-range-sum-queries dynamic-range-minimum-queries dynamic-range-minimum-queries-2 range-xor-queries range-update-queries forest-queries hotel-queries list-removals salary-queries salary-queries-2 pizzeria-queries distinct-values-queries distinct-values-queries-2 forest-queries-II

TREE_ALGORITHM_PROBLEMS=

MATHEMATICS_PROBLEMS=

STRING_ALGORITHM_PROBLEMS=

GEOMETRY_PROBLEMS=

ADVANCED_TECHNIQUE_PROBLEMS=

ADDITIONAL_PROBLEMS=

PROBLEMS=$(INTRODUCTORY_PROBLEMS) $(TREE_ALGORITHM_PROBLEMS) $(SORTING_AND_SEARCHING_PROBLEMS) $(DYNAMIC_PROGRAMMING_PROBLEMS) $(GRAPH_ALGORITHM_PROBLEMS) $(RANGE_QUERY_PROBLEMS) $(TREE_ALGORITHM_PROBLEMS) $(MATHEMATICS_PROBLEMS) $(STRING_ALGORITHM_PROBLEMS) $(GEOMETRY_PROBLEMS) $(ADVANCED_TECHNIQUE_PROBLEMS) $(ADDITIONAL_PROBLEMS)

CXXFLAGS=-std=c++20 -Wall -Og -g -Wno-sign-compare

PRECOMPILED_HEADERS=pch/bits/stdc++.h.gch

all: $(PRECOMPILED_HEADERS) $(PROBLEMS)

pch/bits/stdc++.h.gch: $(wildcard /usr/include/c++/*/x86_64-pc-linux-gnu/bits/stdc++.h)
	mkdir -p pch/bits/
	g++ -x c++-header $(CXXFLAGS) -o $@ -c $<

%: %.cc $(PRECOMPILED_HEADERS)
	$(CXX) $(CXXFLAGS) -I pch -Winvalid-pch -o $@ $< $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROBLEMS) $(PRECOMPILED_HEADERS)
