#include <vector>
#include <iostream>
#include "doctest.h"
#include "backtracking.h"

TEST_CASE("Backtracking") {
  std::cout << "Running: Backtracking:"; 
  std::vector<std::vector<int>> affinities = {
    {0},
    {4, 5},
    {7},
    {5},
    {1, 6},
    {1, 3},
    {4},
    {2},
  };

  std::vector<std::vector<int>> conflicts = {
    {0},
    {2, 3},
    {1, 3},
    {1, 2, 4},
    {3, 5},
    {4, 6, 7},
    {5, 7},
    {5, 6},
  };

  std::vector<int> g(8);

  Problem P { 
    .opt = 112345,
    .number_of_heroes = 7,
    .conflicts_cnt = 0,
    .g = g,
    .affinities = affinities, 
    .conflicts = conflicts,
  };

  SUBCASE("No pruning") {
    std::cout << " [No pruning]";
    int min = backtrackNoPruning(P, 7);
    CHECK(min == 4);
  } 

  SUBCASE("Optimality Pruning") {
    std::cout << " [Optimality pruning]";
    int opt = 112345;
    int min = backtrackOptimalityPruning(P, 7, opt);
    CHECK(min == 4);
  }

  std::cout << "\n";
}
