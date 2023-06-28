#include <vector>
#include <iostream>

#include "limiting-function.h"

int main() {
  std::vector<std::vector<int>> g(4);
  g[1].push_back(2);
  g[1].push_back(3);

  g[2].push_back(1);
  g[2].push_back(3);

  g[3].push_back(1);
  g[3].push_back(2);

  //std::cout << countEvenCycles(g, 1);
}
