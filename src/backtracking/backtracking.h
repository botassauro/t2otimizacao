#ifndef __BACKTRACKING__
#define __BACKTRACKING__

#include <vector>

int backtracking_no_pruning(std::vector<int> g, std::vector<std::vector<int>> affinities, std::vector<std::vector<int>> conflicts, int n);

int backtracking_only_optimality_pruning(std::vector<int> g, std::vector<std::vector<int>> affinities, std::vector<std::vector<int>> conflicts, int n, int& opt, int conflicts_choosen);

#endif
