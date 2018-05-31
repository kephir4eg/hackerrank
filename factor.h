#ifndef FACTOR_H
#define FACTOR_H

#include <algorithm>
#include <bithacks.h>

namespace numeric
{
  /**
   * Find GCD of two numbers, Stein's algorithm, from Wikipedia.
   *
   * NOTE (quote from wiki) : For arbitrary-precision arithmetic, neither the 
   * Euclidean algorithm nor the binary GCD algorithm are fastest, as they both 
   * take time that is a quadratic function of the number of input digits. Instead, 
   * recursive methods that combine ideas from the binary GCD algorithm with the 
   * Schönhage–Strassen algorithm for fast integer multiplication can find GCDs in 
   * near-linear time.
   */
  uint32_t gcd(uint32_t u, uint32_t v)
  {
    /* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
    if (u == 0) { return v; }
    if (v == 0) { return u; }

    int u_lsb = bithacks::lsb(u);
    int v_lsb = bithacks::lsb(v);
    int common_lsb = std::min(u_lsb, v_lsb);

    u >>= u_lsb;

    /* From here on, u is always odd. */
    do {
      /* remove all factors of 2 in v -- they are not common */
      v >>= v_lsb;

      /* Now u and v are both odd. */
      if (u > v) { std::swap(u, v); }

      v -= u;
      v_lsb = bithacks::lsb(v);
    } while (v != 0);

    /* restore common factors of 2 */
    return u << common_lsb;
  }

  inline uint32_t fasthash(uint32_t x) {
      return ((x >> 16) ^ x) * 0x45d9f3b;
  }

  inline uint32_t hash(uint32_t x) {
      x = fasthash(fasthash(x));
      return (x >> 16) ^ x;
  }
/*
  template<int FIXED_SIZE = 10*1024>
  struct fast_assoc_cache
  {
    uint32_t results[10*1024];
    
    
  };

  struct gcd_cached {
    uint32_t results[10*1024];

    uint32_t operator()(uint32_t u, uint32_t v) {
      if (cache) {
      }
    }
  };
*/
};

#endif /* FACTOR_H */
