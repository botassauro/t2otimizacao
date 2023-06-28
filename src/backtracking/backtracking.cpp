#include <vector>
#include <iostream>
#include "limiting-function.h"
#include "backtracking.h"

#define oo 112345

bool noGroupIsEmpty(int zeros, int ones) {
  return zeros == 0 && ones > 0;
}

bool isViable(Problem& P) {
  return true;
  int zeros = 0;
  int ones = P.number_of_heroes;

  for ( int h = 1; h <= P.number_of_heroes; h++ ) {
    zeros +=  P.g[h];
    ones -=  P.g[h];

    for ( int u : P.affinities[h] ) {
      if ( P.g[h] != P.g[u] ) 
        return false;
    }
  }

  return noGroupIsEmpty(zeros, ones);
}

int conflictsInserted(Problem P, int h) {
  int cnt = 0;

  for ( int u : P.conflicts[h] ) {
    if ( P.g[h] == P.g[u] ) { 
      cnt++;
    }
  }

  return cnt;
}

int backtrackNoPruning(Problem P, int h) {
  if ( h == 0 ) {
    return isViable(P) ? 0 : oo;
  }

  int min = oo;

  for (int i = 0; i <= 1; i++ ) {
    P.g[h] = i;
    int min_group = backtrackNoPruning(P, h-1) + conflictsInserted(P, h);
    min = std::min(min, min_group);
  }

  return min;
}

std::vector<std::vector<int>> removeConflicts(std::vector<std::vector<int>> conflicts, int h) {
  for ( int u : conflicts[h] ) {
    if ( u > h ) {
      conflicts[h].erase(conflicts[h].begin() + u);             
      conflicts[u].erase(conflicts[u].begin() + h);             
    }
  }

  return conflicts;
}

int backtrackOptimalityPruning(Problem P, int h, int& opt) {
  if ( h == 0 ) {
    return isViable(P) ? 0 : oo;
  }
  
  if ( limitingFunction(P.conflicts, P.conflicts_cnt) >= P.opt ) {
    return oo;
  }

  std::vector<std::vector<int>> original_conflicts = P.conflicts;

  int min = oo;

  for ( int i = 0; i <= 1; i++ ) {
    P.g[h] = i;
    int conflicts_inserted = conflictsInserted(P, h);
    P.conflicts_cnt += conflicts_inserted;
    P.conflicts = removeConflicts(P.conflicts, h);
    int min_group = backtrackOptimalityPruning(P, h-1, opt) + conflicts_inserted;

    min = std::min(min, min_group);

    P.conflicts_cnt -= conflicts_inserted;
    P.conflicts = original_conflicts;
  }

  opt = std::min(opt, min);

  return min;
}

// bool wouldBeViable(std::vector<int> g, std::vector<std::vector<int>> affinities, int h, int h_group) {
//   for ( int u : affinities[h] ) {
//     if ( h_group != g[u] ) {
//       return false;
//     }
//   }

//   return true;
// }
//   
// int backtrackingViabilityPruning(std::vector<int> g, std::vector<std::vector<int>> affinities, std::vector<std::vector<int>> conflicts, int h) {
//   if ( h == 0 ) {
//     return isViable(g, affinities) ? 0 : oo;
//   }
//   
//   int group0 = oo;
//   int group1 = oo;

//   if ( wouldBeViable(g, affinities, h, 1) ) {
//     g[h] = 1;
//     group0 = backtrackingViabilityPruning(g, affinities, conflicts, h-1) + conflictsInserted(g, conflicts[n], n);
//   }

//   if ( wouldBeViable(g, affinities, h, 0) ) {
//     g[h] = 0;
//     group1 = backtrackingViabilityPruning(g, affinities, conflicts, h-1) + conflictsInserted(g, conflicts[n], n);
//   }

//   return std::min(group0, group1);
// }
