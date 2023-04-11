#ifndef DUMP_H_INCLUDED

#include <iostream>
#include <tuple>

// I stole this from: https://www.scs.stanford.edu/~dm/blog/va-opt.html
#define PARENS ()
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__
#define FOR_EACH(macro, ...) __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...) macro(a1) __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

// DUMP(x, y, z) dumps the values of expressions x, y and z to std::cerr.
//
// Note that there must be an overload of ostream& operator<<(ostream&)
// for each of the value's types.
//
// For example:
//
//   int i = 42;
//   const char *s = "foo";
//   DUMP(i, 3*i, s);
//
// Outputs:
//
//   10: i=42 3*i=126 s=foo
//
// where 10 is the line number of the DUMP call.
#define DUMP_ARG(x) << " " #x "=" << (x)
#define DUMP(...) std::cerr << __LINE__ << ":" FOR_EACH(DUMP_ARG, __VA_ARGS__) << std::endl;

#endif // ndef DUMP_H_INCLUDED
