#ifndef __BACKTRACKING__
#define __BACKTRACKING__

#include <vector>

struct Problem {
  int opt;
  int number_of_heroes;
  int conflicts_cnt;
  std::vector<int> g;
  std::vector<std::vector<int>> affinities;
  std::vector<std::vector<int>> conflicts;
};

int backtracking(bool countTriangles, bool desactivateOptimality, bool desactivateViability, Problem P, std::vector<int>& S);

int backtrackingNoPruning(Problem P, int h, std::vector<int>& S);
int backtrackingViabilityPruning(Problem P, int h, std::vector<int>& S);
int backtrackingOptimalityPruning(Problem P, int h, int& opt, std::vector<int>& S, bool countTriangles);
int backtrackingViabilityAndOptimalityPruning(Problem P, int h, int& opt, std::vector<int>& S, bool countTriangles);

#endif
