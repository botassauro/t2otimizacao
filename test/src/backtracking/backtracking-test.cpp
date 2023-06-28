#include <vector>
#include "doctest.h"
#include "backtracking.h"

TEST_CASE("backtracking") {
 
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
    {4},
    {5},
    {6, 7},
    {5, 7},
    {5, 6},
  };

  std::vector<int> g(7);

  SUBCASE("No pruning") {
    int min = backtracking_no_pruning(g, affinities, conflicts, 7);
    CHECK(min == 4);
  } 

  SUBCASE("Optimality Pruning") {
    int opt = 112345;
    int min = backtracking_only_optimality_pruning(g, affinities, conflicts, 7, opt, 0);
    CHECK(min == 4);
  }
}
