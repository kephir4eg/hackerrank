#include <stdlib.h>
#include <iostream>

#include <collatz.h>

int test_01(int argc, char **argv)
{
  collatz_solver_t solver;
  std::cout << solver(0x80000) << std::endl;
}

int main(int argc, char **argv) {
  collatz_solver_t solver;

  int n;
  std::cin >> n;

  while (n > 0)
  {
    int x;
    std::cin >> x;
    std::cout << solver(x) << std::endl;
    --n;
  }

  return 0;
}
