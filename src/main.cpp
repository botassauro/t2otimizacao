#include <vector>

#include "utils.h"
#include "backtracking.h"
#include "limiting-function.h"

int main() {
  Problem P;
  P = readHeroes();

  int opt = 112345;
  std::vector<int> S(P.number_of_heroes+1);
  int min = backtrackingViabilityAndOptimalityPruning(P, P.number_of_heroes, opt, S);

  printSolution(S, min);
}
