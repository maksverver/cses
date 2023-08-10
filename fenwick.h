// Implementation of Fenwick arrays, aka Fenwick trees aka Binary Indexed Trees.
//
// Keep in sync with Codelib2/fenwick.cc

#ifndef FENWICK_H_INCLUDED
#define FENWICK_H_INCLUDED

#include <bit>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

// Converts a regular array into a Fenwick array (in linear time).
template <class T> void fenwick_construct(std::vector<T> &a) {
  for (size_t i = 1; i < a.size(); i = 2 * i)
    for (size_t j = 2 * i - 1; j < a.size(); j += 2 * i)
      a[j] += a[j - i];
}

// Converts a Fenwick array back into a regular array (in linear time).
template <class T> void fenwick_destruct(std::vector<T> &a) {
  size_t i = 1;
  while (2 * i < a.size()) i <<= 1;
  for (; i > 0; i >>= 1)
    for (size_t j = 2 * i - 1; j < a.size(); j += 2 * i)
      a[j] -= a[j - i];
}

// Calculates the sum of the first `n` elements in `a` (which are the elements
// with zero-based indices strictly less than n). */
template <class T> T fenwick_prefixsum(const std::vector<T> &a, size_t n) {
  T res = 0;
  while (n > 0) res += a[n - 1], n &= n - 1;
  return res;
}

// Calculates the sum of elements from index i to j (exclusive).
template <class T> T fenwick_rangesum(const std::vector<T> &a, size_t i, size_t j) {
  return i < j ? fenwick_prefixsum(a, j) - fenwick_prefixsum(a, i) : 0;
}

// Adds `v` to the value stored at index `i`.
template <class T> void fenwick_update(std::vector<T> &a, size_t i, T v) {
  while (i < a.size()) a[i] += v, i |= i + 1;
}

// Retrieves the value stored at index `i`.
template <class T> T fenwick_retrieve(const std::vector<T> &a, size_t i) {
  T res = a[i];
  for (size_t bit = 1; i & bit; bit += bit) res -= a[i ^ bit];
  return res;
}

// Resizes the Fenwick array `a` to size `new_size` (which may be less or
// greater than the current size).  Note that shrinking a Fenwick array is
// simply truncating the underlying array.
//
// Increasing the size takes runs in O(M log N) where M = new_size - old_size.
// It should be possible to do it in O(M)?
template <class T> void fenwick_resize(std::vector<T> &a, size_t new_size) {
  size_t old_size = a.size();
  a.resize(new_size);
  for (size_t i = old_size; i < new_size; ++i) a[i] -= fenwick_retrieve(a, i);
}

// Assuming all values are nonnegative, returns the least index `n` such that
// fenwick_prefixsum(a, n) >= sum, or returns a.size() + 1 if there is none.
template <class T> size_t fenwick_lowerbound(const std::vector<T> &a, T sum) {
  size_t n = 0;
  for (size_t bit = std::bit_floor(a.size()); bit; bit >>= 1) {
    if (n + bit <= a.size() && sum > a[n + bit - 1]) {
      sum -= a[n + bit - 1];
      n += bit;
    }
  }
  return n + (sum > 0);
}

// Assuming all values are nonnegative, returns the least index `n` such that
// fenwick_prefixsum(a, n) > sum, or returns a.size() + 1 if there is none.
template <class T> size_t fenwick_upperbound(const std::vector<T> &a, T sum) {
  size_t n = 0;
  for (size_t bit = std::bit_floor(a.size()); bit; bit >>= 1) {
    if (n + bit <= a.size() && sum >= a[n + bit - 1]) {
      sum -= a[n + bit - 1];
      n += bit;
    }
  }
  return n + (sum >= 0);
}

#endif // ndef FENWICK_H_INCLUDED
