#ifndef MOD_INT_H_INCLUDED
#define MOD_INT_H_INCLUDED

#include <cassert>
#include <concepts>
#include <iostream>

// ModInt models an element in the ring of integers modulo M.
//
// Type parameters:
//
//  - M: the positive integer modulus.
//  - I: an integer type large enough to store M.
//  - L: an integer type large enough to store M * M.
//
// It's often useful to create a type alias. Example:
//
//  using MI = ModInt<int32_t, int64_t, 1000000007>;
//
// Most arithmetic operators are defined with the expected semantics. The
// following operators are omited because they have no obvious semantics:
//  <, <=, >, >=, %, !, &&, ||, &, |, ^, <<, >>
// and the associated assignment operators (%= etc.)
//
// The division and inverse operators require that M is a prime number!
//
template<class I, class L, I M>
class ModInt {
  using S = ModInt<I, L, M>;

  // The integer value normalized into the range from 0 and M (exclusive).
  I i;

  // Arithmetic operations on integers. Assumes `a` and `b` are normalized,
  // and returns a normalized value. The implementation is designed to avoid
  // overflow.
  static I Add(I a, I b) { return b < M - a ? a + b : b - (M - a); }
  static I Sub(I a, I b) { return a < b ? M - b + a : a - b; }
  static I Mul(I a, I b) { return L{a} * L{b} % M; }
  static I Inc(I a) { return a + 1 < M ? a + 1 : 0; }
  static I Dec(I a) { return a > 0 ? a - 1 : M - 1; }
  static I Neg(I a) { return a > 0 ? M - a : 0; }

public:
  ModInt() : i(0) {}
  ModInt(L l) : i(l % M) { if (i < 0) i += M; }

  ModInt(const S &a) = default;
  S& operator=(const S&) = default;

  bool operator==(const S &a) const { return i == a.i; }
  bool operator!=(const S &a) const { return i != a.i; }

  S& operator+=(const S &a) { i = Add(i, a.i); return *this; }
  S& operator-=(const S &a) { i = Sub(i, a.i); return *this; }
  S& operator*=(const S &a) { i = Mul(i, a.i); return *this; }
  S& operator/=(const S &a) { return *this *= a.Inverse(); }

  S& operator++() { i = Inc(i); return *this; }
  S& operator--() { i = Dec(i); return *this; }
  S operator++(signed) { S r = *this; i = Inc(i); return r; }
  S operator--(signed) { S r = *this; i = Dec(i); return r; }

  S& Negate() { i = Neg(i); return *this; }

  // Returns this value raised to the e-th power. Runs in O(log e) time using
  // exponentiation by squaring.
   S Pow(std::integral auto e) const {
    assert(e >= 0);
    S res = 1;
    for (S x = *this; e > 0; e >>= 1) {
      if (e & 1) res *= x;
      x *= x;
    }
    return res;
  }

  // Calculates the inverse (1/i) as i^(M - 2). M must be prime.
  // From Fermat's little theorem (assuming p is a prime):
  //    i^p     = i       (mod p)
  //    i^(p-1) = 1       (mod p)
  //    i^(p-2) = p^(-1)  (mod p)
  S Inverse() const {
    assert(IsNonzero());
    return Pow(M - 2);
  }

  S operator+() const { return *this; }
  S operator-() const { S r = *this; r.Negate(); return r; }

  S operator+(const S &a) const { S r = *this; r += a; return r; }
  S operator-(const S &a) const { S r = *this; r -= a; return r; }
  S operator*(const S &a) const { S r = *this; r *= a; return r; }
  S operator/(const S &a) const { S r = *this; r /= a; return r; }

  bool IsZero() const { return i == 0; }
  bool IsNonzero() const { return !IsZero(); }
  I Int() const { return i; }

  explicit operator bool() { return IsNonzero(); }
  explicit operator I() { return Int(); }
};

template<class I, class L, I M>
std::ostream &operator<<(std::ostream &os, const ModInt<I, L, M> &a) {
  return os << a.Int();
}

template<class I, class L, I M>
std::istream &operator>>(std::istream &is, ModInt<I, L, M> &a) {
  L l;
  is >> l;
  a = l;
  return is;
}

#endif  // ndef MOD_INT_H_INCLUDED
