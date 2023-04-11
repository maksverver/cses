possible = set()
for x in range(100):
  for y in range(x, 100):
    A = 2*x + y
    B = x + 2*y
    assert A <= B
    print(x, y, A, B, (A+B)%3, B <= 2*A)
    possible.add((A, B))

for a in range(100):
  for b in range(a, 100):
    if (a + b) % 3 == 0 and b <= 2*a:
      print(a, b, (a, b) in possible)
