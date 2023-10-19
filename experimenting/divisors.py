def Divisors(x):
  '''Given a positive integer x, returns a new list with the divisors of x,
     in sorted order, including 1 and x itself.'''
  assert isinstance(x, int) and x > 0
  a = []
  b = []
  for d in range(1, int(x**.5) + 1):
    if x % d == 0:
      a.append(d)
      if (e := x // d) > d:
        b.append(e)
  b.reverse()
  return a + b

assert Divisors(1) == [1]
assert Divisors(2) == [1, 2]
assert Divisors(7) == [1, 7]
assert Divisors(20) == [1, 2, 4, 5, 10, 20]
assert Divisors(81) == [1, 3, 9, 27, 81]
