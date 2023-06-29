#include <vector>
#include <iostream>
#include "doctest.h"
#include "backtracking.h"

TEST_CASE("Backtracking case 1") {
  std::cout << "Running: Backtracking case 1:"; 
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

  std::vector<int> g(8, -1);

  Problem P { 
    .opt = 112345,
    .number_of_heroes = 7,
    .conflicts_cnt = 0,
    .g = g,
    .affinities = affinities, 
    .conflicts = conflicts,
  };

  int nodes = 0;
  std::vector<int> S(8);

  SUBCASE("No pruning") {
    std::cout << " [No pruning]";
    int min = backtrackingNoPruning(P, 7, S, nodes);
    CHECK(min == 4);
  } 

  SUBCASE("Viability Pruning") {
    std::cout << " [Viability pruning]";
    int min = backtrackingViabilityPruning(P, 7, S, nodes);
    CHECK(min == 4);
  }
  
  SUBCASE("Optimality Pruning") {
    std::cout << " [Optimality pruning]";
    int opt = 112345;
    int min = backtrackingOptimalityPruning(P, 7, opt, S, false, nodes);
    CHECK(min == 4);
  }

  SUBCASE("Viability and Optimality Pruning") {
    std::cout << " [Viability and optimality pruning]";
    int opt = 112345;
    int min = backtrackingViabilityAndOptimalityPruning(P, 7, opt, S, false, nodes);
    CHECK(min == 4);
  }
  std::cout << "\n";
}

TEST_CASE("Backtracking case 2") {
  std::cout << "Running: Backtracking case 2:"; 

  std::vector<std::vector<int>> affinities = {
    {0},
    {5},
    {},
    {},
    {},
    {1},
  };

  std::vector<std::vector<int>> conflicts = {
    {0},
    {2, 3},
    {1, 3, 4},
    {1, 2, 4, 5},
    {2, 3},
    {3},
  };

  int nodes = 0;
  std::vector<int> g(6, -1);

  Problem P { 
    .opt = 112345,
    .number_of_heroes = 5,
    .conflicts_cnt = 0,
    .g = g,
    .affinities = affinities, 
    .conflicts = conflicts,
  };

  std::vector<int> S(6);

  SUBCASE("No pruning") {
    std::cout << " [No pruning]";
    int min = backtrackingNoPruning(P, 5, S, nodes);
    CHECK(min == 1);
  } 

  SUBCASE("Viability Pruning") {
    std::cout << " [Viability pruning]";
    int min = backtrackingViabilityPruning(P, 5, S, nodes);
    CHECK(min == 1);
  }
  
  SUBCASE("Optimality Pruning") {
    std::cout << " [Optimality pruning]";
    int opt = 112345;
    int min = backtrackingOptimalityPruning(P, 5, opt, S, false, nodes);
    CHECK(min == 1);
  }

  SUBCASE("Viability and Optimality Pruning") {
    std::cout << " [Viability and optimality pruning]";
    int opt = 112345;
    int min = backtrackingViabilityAndOptimalityPruning(P, 5, opt, S, false, nodes);
    CHECK(min == 1);
  }

  std::cout << "\n";
}

TEST_CASE("Backtracking case 3") {
  std::cout << "Running: Backtracking case 3:"; 

  std::vector<std::vector<int>> affinities = {
    {},
    {6},
    {4},
    {7},
    {2},
    {},
    {1},
    {3}
  };

  std::vector<std::vector<int>> conflicts = {
    {0},
    {2, 3},
    {1, 3},
    {1, 2, 4, 5},
    {3},
    {3, 6, 7},
    {5},
    {5}
  };

  std::vector<int> g(8, -1);

  Problem P { 
    .opt = 112345,
    .number_of_heroes = 7,
    .conflicts_cnt = 0,
    .g = g,
    .affinities = affinities, 
    .conflicts = conflicts,
  };

  int nodes = 0;
  std::vector<int> S(8);

  SUBCASE("No pruning") {
    std::cout << " [No pruning]";
    int min = backtrackingNoPruning(P, 7, S, nodes);
    CHECK(min == 1);
  } 

  SUBCASE("Viability Pruning") {
    std::cout << " [Viability pruning]";
    int min = backtrackingViabilityPruning(P, 7, S, nodes);
    CHECK(min == 1);
  }
  
  SUBCASE("Optimality Pruning") {
    std::cout << " [Optimality pruning]";
    int opt = 112345;
    int min = backtrackingOptimalityPruning(P, 7, opt, S, false, nodes);
    CHECK(min == 1);
  }

  SUBCASE("Viability and Optimality Pruning") {
    std::cout << " [Viability and optimality pruning]";
    int opt = 112345;
    int min = backtrackingViabilityAndOptimalityPruning(P, 7, opt, S, false, nodes);
    CHECK(min == 1);
  }

  std::cout << "\n";
}
