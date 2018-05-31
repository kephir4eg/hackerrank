#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>

#include "factor.h"

namespace geometry {


/* Represents a line */
struct line_t
{
  int a, b, c;

  line_t(int a_a, int a_b, int a_c)
    : a(a_a), b(a_b), c(a_c)
  {
    normalize();
  }

  line_t(const line_t & x)
    : a(x.a), b(x.b), c(x.c) { }

  line_t(int x1, int y1, int x2, int y2)
    : a(y2 - y1), b(x1 - x2), c(x2*y1 - x1*y2)
  {
    normalize();
  }

  int operator ()(int x, int y) const { return a*x + b*y + c; }

  bool invalid() const { return (a == 0) && (b == 0); }

  void normalize() {
#ifdef SAFE_NORMALIZE
    if (invalid()) return;
#endif /* SAFE_NORMALIZE */
    int gcd = numeric::gcd(numeric::gcd(abs(a), abs(b)), abs(c));

    a /= gcd;
    b /= gcd;
    c /= gcd;
  }

  int hash() {
    return (numeric::fasthash(a) ^ numeric::fasthash(b) ^ numeric::fasthash(c));
  }

  bool parallel(const line_t & x) const {
    return (a == x.a) && (b == x.b);
  }

  bool operator | (const line_t & x) const { return parallel(x); }

  bool operator == (const line_t & x) const {
    return (a == x.a) && (b == x.b) && (c == x.c);
  }
};

std::ostream & operator << (std::ostream & stream, const line_t & x)
{
  return stream << "line(" << x.a << " " << x.b << " " << x.c << ")";
}

}

#endif /* GEOMETRY_H */
