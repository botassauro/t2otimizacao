#include <vector>
#include "limiting-function.h"
#include "backtracking.h"

#define oo 112345

bool isViable(std::vector<int> g, std::vector<std::vector<int>> affinities) {
  return true;
  int all_zeros = 0;
  int all_ones = 0;

  for ( size_t h = 1; h <= g.size(); h++ ) {
    all_zeros +=  g[h];
    all_ones +=  g[h];

    for ( size_t u = 1; u <= affinities[h].size(); u++ ) {
      if ( g[h] != g[u] ) 
        return false;
    }
  }

  return (all_zeros != 0) && (all_ones != (int)(g.size() - 1));
}

int countConflicts(std::vector<int> g, std::vector<std::vector<int>> conflicts) {
  int cnt = 0;

  for ( size_t h = 1; h <= conflicts.size(); h++ ) {
    for ( size_t u = 1; u <= conflicts[h].size(); u++ ) {
      if ( g[h] == g[u] )
        cnt++;
    }
  }

  return cnt;
}

int backtracking_no_pruning(std::vector<int> g, std::vector<std::vector<int>> affinities, std::vector<std::vector<int>> conflicts, int n) {
  if ( n == 0 ) {
    return isViable(g, affinities) ? countConflicts(g, conflicts) : oo;
  }
  
  g[n] = 1;
  int try_group_0 = backtracking_no_pruning(g, affinities, conflicts, n-1);

  g[n] = 0;
  int try_group_1 = backtracking_no_pruning(g, affinities, conflicts, n-1);

  return std::min(try_group_0, try_group_1);
}

int conflictsInserted(std::vector<int> g, std::vector<int> conflicts, int h) {
  int cnt = 0;

  for ( int u = 1; u <= conflicts[h]; u++ ) {
    if ( g[h] == g[u] ) 
      cnt++;
  }

  return cnt;
}

int backtracking_only_optimality_pruning(std::vector<int> g, std::vector<std::vector<int>> affinities, std::vector<std::vector<int>> conflicts, int n, int& opt, int conflicts_choosen) {
  if ( n == 0 ) {
    return isViable(g, affinities) ? countConflicts(g, conflicts) : oo;
  }
  
  if ( limitingFunction(conflicts, conflicts_choosen) >= opt ) {
    return oo;
  }

  conflicts.erase(conflicts.begin()+n+1);
  g[n] = 1;
  int conflicts_aux = conflicts_choosen + conflictsInserted(g, conflicts[n], n);
  int try_group_0 = backtracking_only_optimality_pruning(g, affinities, conflicts, n-1, opt, conflicts_aux);

  g[n] = 0;
  conflicts_aux = conflicts_choosen + conflictsInserted(g, conflicts[n], n);
  int try_group_1 = backtracking_only_optimality_pruning(g, affinities, conflicts, n-1, opt, conflicts_aux);

  if ( try_group_0 < try_group_1 ) {
    if ( try_group_0 > opt ) {
      opt = try_group_0;
    }
    g[n] = 1;
    return try_group_0;
  }

  if ( try_group_1 > opt ) {
    opt = try_group_1;
  }
  
  return try_group_1;
}
