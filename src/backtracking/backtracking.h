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

int backtrackNoPruning(Problem P, int h);
int backtrackOptimalityPruning(Problem P, int h, int& opt);

int backtrackingViabilityPruning(std::vector<int> g, std::vector<std::vector<int>> affinities, std::vector<std::vector<int>> conflicts, int h);
#endif
