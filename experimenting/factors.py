def Factors(x):
  '''Given a positive integer x, returns the prime factorization x, as list of
     (p, k) tuples, where p is a prime number and k is a positive exponent.'''
  assert isinstance(x, int) and x > 0
  result = []
  p = 2
  while p*p <= x:
    k = 0
    while x % p == 0:
      k += 1
      x //= p
    if k > 0:
      result.append((p, k))
    p += 1
  if x > 1:
    result.append((x, 1))
  return result

assert Factors(1) == []
assert Factors(2) == [(2, 1)]
assert Factors(7) == [(7, 1)]
assert Factors(20) == [(2, 2), (5, 1)]
assert Factors(81) == [(3, 4)]
