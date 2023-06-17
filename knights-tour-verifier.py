#!/usr/bin/env python3

import sys

grid = [list(map(int, sys.stdin.readline().split())) for _ in range(8)]

sequence = [(grid[r][c], r, c) for r in range(8) for c in range(8)]
sequence.sort()

last_i, last_r, last_c = sequence[0]
print('Starts at', (last_c + 1, last_r + 1))
assert last_i == 1
for next_i, next_r, next_c in sequence[1:]:
  assert next_i == last_i + 1
  dr = next_r - last_r
  dc = next_c - last_c
  assert (abs(dr) == 1 and abs(dc) == 2) or (abs(dr) == 2 and abs(dc) == 1)
  last_i, last_r, last_c = next_i, next_r, next_c
  #print(last_i, last_r, last_c)
print('Ends at', (last_c + 1, last_r + 1))
