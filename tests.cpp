#include <stdlib.h>
#include <iostream>

#include "factor.h"

#define SAFE_NORMALIZE

#include "geometry.h"

static const int points[] = { 
    1,1,5,5, 2,2,6,6,
    0,0,1,0, 0,0,0,1,
    0,0,0,0, 0,0,0,0,
    0,0,2,3, 2,3,343,5252 };

#define sizeof_array(X) (sizeof(X) / sizeof(*(X)))

void test_lines()
{
  for (int i = 0; i < sizeof_array(points) / 8; ++i) {
    const int * p = points + i*8;

    geometry::line_t x(p[0], p[1], p[2], p[3]);
    geometry::line_t y(p[4], p[5], p[6], p[7]);

    std::cout << x << " " << x(p[0], p[1]) << " " << x(p[2], p[3]) << std::endl;
    std::cout << y << " " << y(p[4], p[5]) << " " << y(p[6], p[7]) << std::endl;;
    std::cout << (x == y) << std::endl;;
  }
}

int main(int argc, char **argv) 
{
  test_lines();

  return 0;
}
