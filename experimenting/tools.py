from functools import reduce
from operator import mul

def Product(a):
  return reduce(mul, a)
