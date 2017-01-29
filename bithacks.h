#ifndef BITHACKS_H
#define BITHACKS_H

namespace bithacks 
{

/**
 * General integer fast 2 factor degree resolution.
 * Return the degree of factor 2 of an integer.
 */
template <typename int_type_t>
inline int lsb(int_type_t v) {
  if (v == 0) {
    return 8 * sizeof(v);
  }

  int c = 0;

  v = (v ^ (v - 1)) >> 1;

  for (c = 0; v; c++) {
    v >>= 1;
  }

  return c;
}

static const int MultiplyDeBruijnBitPosition[32] = 
{
  0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
  31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};

/**
 * Specialized degree of factor 2 evaluation optimized for uint32_t,
 * which is 99% of cases. Requires 1 multiplication and 1 lookup.
 */
template <>
inline int lsb(uint32_t v) {
  return MultiplyDeBruijnBitPosition[((uint32_t)((v & -v) * 0x077CB531U)) >> 27];
}

};

#endif /* BITHACKS_H */
