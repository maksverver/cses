from functools import reduce
from operator import mul

def Product(a):
  return reduce(mul, a)

def Factorial(n):
  assert isinstance(n, int) and n >= 0
  return reduce(mul, range(1, n + 1), 1)
