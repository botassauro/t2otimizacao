#include <vector>
#include <unistd.h>

#include "utils.h"
#include "backtracking.h"
#include "limiting-function.h"

int main(int argc, char** argv) {
  Problem P;
  P = readHeroes();
  std::vector<int> S(P.number_of_heroes+1);

  int op;
  bool countTriangles = false;
  bool desactivateOptimality = false;
  bool desactivateViability = false;

  while( (op = getopt(argc, argv, "foa")) != -1 ) {
    switch (op) {
      case 'a':
        countTriangles = true;
        break;

      case 'o':
        desactivateOptimality = true;
        break;

      case 'f':
        desactivateViability = true;
        break;

      default: 
        break;
    }
  }

  int nodes = 0;
  int min = backtracking(countTriangles, desactivateOptimality, desactivateViability, P, S, nodes);
  printSolution(S, min, nodes);
}
