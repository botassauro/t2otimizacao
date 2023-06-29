#include <vector>
#include <iostream>
#include "limiting-function.h"
#include "backtracking.h"

#define oo 112345
#define NO_GROUP -1

bool noGroupIsEmpty(int zeros, int ones) {
  return zeros != 0 && ones > 0;
}

bool isViable(Problem P) {
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

int backtrackingNoPruning(Problem P, int h, std::vector<int>& S) {
  if ( h == 0 ) {
    S = P.g;
    return isViable(P) ? 0 : oo;
  }

  int min = oo;

  std::vector<int> sol_aux;
  for (int i = 0; i <= 1; i++ ) {
    P.g[h] = i;
    int min_group = backtrackingNoPruning(P, h-1, sol_aux) + conflictsInserted(P, h);

    if ( min_group <= min ) {
      S = sol_aux;
      min = min_group;
    }
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

int backtrackingOptimalityPruning(Problem P, int h, int& opt, std::vector<int>& S, bool countTriangles) {
  if ( h == 0 ) {
    S = P.g;
    return isViable(P) ? 0 : oo;
  }
  
  if ( limitingFunction(P.conflicts, P.conflicts_cnt, countTriangles) >= P.opt ) {
    return oo;
  }

  int min = oo;
  std::vector<std::vector<int>> original_conflicts = P.conflicts;
  std::vector<int> sol_aux;

  for ( int i = 0; i <= 1; i++ ) {
    P.g[h] = i;
    int conflicts_inserted = conflictsInserted(P, h);
    P.conflicts_cnt += conflicts_inserted;
    P.conflicts = removeConflicts(P.conflicts, h);
    int min_group = backtrackingOptimalityPruning(P, h-1, opt, sol_aux, countTriangles) + conflicts_inserted;

    if ( min_group <= min ) {
      S = sol_aux;
      min = min_group;
    }

    P.conflicts_cnt -= conflicts_inserted;
    P.conflicts = original_conflicts;
  }

  opt = std::min(opt, min);

  return min;
}

bool wouldBeViable(Problem P, int h, int h_group) {
  for ( int u : P.affinities[h] ) {
    if ( P.g[u] == NO_GROUP ) {
      continue;
    }

    if ( P.g[u] != h_group ) {
      return false;
    }
  }

  return true;
}
  
int backtrackingViabilityPruning(Problem P, int h, std::vector<int>& S) {
  if ( h == 0 ) {
    S = P.g;
    return isViable(P) ? 0 : oo;
  }
  
  int min = oo;
  std::vector<int> sol_aux;

  for ( int i = 0; i <= 1; i++ ) {
    if ( wouldBeViable(P, h, i) ) {
      P.g[h] = i;
      int min_group = backtrackingViabilityPruning(P, h-1, sol_aux) + conflictsInserted(P, h);

      if ( min_group <= min ) {
        S = sol_aux;
        min = min_group;
      }
    }
  }

  return min;
}

int backtrackingViabilityAndOptimalityPruning(Problem P, int h, int& opt, std::vector<int>& S, bool countTriangles) {
  if ( h == 0 ) {
    S = P.g;
    return isViable(P) ? 0 : oo;
  }
  
  if ( limitingFunction(P.conflicts, P.conflicts_cnt, countTriangles) >= P.opt ) {
    return oo;
  }

  std::vector<std::vector<int>> original_conflicts = P.conflicts;

  int min = oo;
  std::vector<int> sol_aux;

  for ( int i = 0; i <= 1; i++ ) {
    if ( wouldBeViable(P, h, i) ) {
      P.g[h] = i;
      int conflicts_inserted = conflictsInserted(P, h);
      P.conflicts_cnt += conflicts_inserted;
      P.conflicts = removeConflicts(P.conflicts, h);
      int min_group = backtrackingOptimalityPruning(P, h-1, opt, sol_aux, countTriangles) + conflicts_inserted;

      if ( min_group <= min ) {
        S = sol_aux;
        min = min_group;
      }

      P.conflicts_cnt -= conflicts_inserted;
      P.conflicts = original_conflicts;
    }
  }

  opt = std::min(opt, min);

  return min;
}

int backtracking(bool countTriangles, bool desactivateOptimality, bool desactivateViability, Problem P, std::vector<int>& S) {
  if ( desactivateOptimality == true && desactivateViability == true ) {
    return backtrackingNoPruning(P, P.number_of_heroes, S);
  }

  if ( desactivateOptimality == true ) {
    return backtrackingViabilityPruning(P, P.number_of_heroes, S);
  }

  if ( desactivateViability == true ) {
    int opt = 112345;
    return backtrackingOptimalityPruning(P, P.number_of_heroes, opt, S, countTriangles);
  }
  
  int opt = 112345;
  return backtrackingViabilityAndOptimalityPruning(P, P.number_of_heroes, opt, S, countTriangles);
}
