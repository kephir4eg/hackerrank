#ifndef COLLATZ_H
#define COLLATZ_H

#include <stdint.h>
#include <bithacks.h>

#include <vector>
#include <map>
#include <limits>
#include <algorithm>
#include <stdexcept>

/* Project Euler #14: Longest Collatz sequence */

struct collatz_length_t
{
  enum { MAX_CACHE = 200*1024 };

  uint16_t cache_32[MAX_CACHE];

  int calc(uint32_t n)
  {
    int initial = n;
    int m;
    bool save_cache = false;

    if ((n % 2) == 1) {
      int nd2 = n >> 1;

      if (nd2 < MAX_CACHE) {
        if (cache_32[nd2] != 0) {
          return cache_32[nd2];
        }

        save_cache = true;
      }
    }

    m = do_calc(n, 0);

    if (save_cache) {
      cache_32[initial / 2] = m;
    }

    return m;
  }

  inline int operator()(uint32_t n) {
    return calc(n);
  }

  inline int overflow(uint64_t n, int m)
  {
    throw std::overflow_error("uint64_t overflow");
  }

  inline int overflow(uint32_t n, int m)
  {
    return do_calc<uint64_t>(n, m);
  }

  template <typename int_type_t>
  int do_calc(int_type_t n, int m)
  {
    /* Make odd */
    int b = bithacks::lsb<int_type_t>(n);
    m += b;
    n >>= b;

    while (n > 1) {
    /* n is odd, but we don't care about even numbers
     * since we can always very easily get the closest odd */

      int_type_t nd2 = n >> 1;

      if (nd2 < MAX_CACHE && cache_32[nd2] != 0) {
        return m + cache_32[nd2];
      }

      if (n > (std::numeric_limits<int_type_t>().max() / 3 * 2 - 1)) {
        return overflow(n, m);
      }

      n += (n + 1) / 2;
      m += 2;

      int b = bithacks::lsb<int_type_t>(n);
      m += b;
      n >>= b;
    }

    return m + 1;
  }
};

struct collatz_solver_t {
  typedef std::map<uint32_t, uint16_t> result_cache_t;

  result_cache_t   result_cache;
  collatz_length_t length_solver;

  collatz_solver_t() {
    result_cache[1] = 1;
    result_cache[2] = 2;
  }

  int solve(uint32_t n);

  inline int operator()(uint32_t n) {
    return solve(n);
  }
};

int collatz_solver_t::solve(uint32_t n)
{
  int max = 1;
  int result = 1;

  /* First, check result cache */

  if (!result_cache.empty()) {
    auto it = result_cache.upper_bound(n);
    bool found = (it != result_cache.end());

    --it;
    max = it->second;
    result = it->first;

    if (found) {
      return result;
    }
  }

  int ir = max;

  /* If not found in result cache, try to fill the next value of the cache,
   * so that we don't need to perform search the next time.
   *
   * i.e. we are trying to find the next nearest collatz number
   */
  for (int i = result + 1; (i < n) || (max == ir); ++i) {
    int v = length_solver(i);

    if (v >= max) {
      max = v;
      result_cache[i] = v;

      if (i <= n) {
        result = i;
      }
    }
  }

  return result;
}

#endif /* COLLATZ_H */
