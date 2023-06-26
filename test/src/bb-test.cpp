#include <iostream>
#include "doctest.h"
#include "bb.h"

TEST_CASE("Count all even cycles") {
  std::cout << "Running: Count all even cycles:";

  SUBCASE("Simple triangle") {
    std::cout << " [Simple triangle]";

    std::vector<std::vector<int>> g {
      {0, 0},
      {2, 3},
      {1, 3},
      {1, 2}
    };

    CHECK(countEvenCycles(g, 1) == 1);
  }

  SUBCASE("Simple square") {
    std::cout << " [Simple square]";

    std::vector<std::vector<int>> g {
      {0, 0},
      {2, 4},
      {1, 3},
      {2, 4},
      {1, 3},
    };

    CHECK(countEvenCycles(g, 1) == 0);
  }

  SUBCASE("Simple pentagon") {
    std::cout << " [Simple pentagon]";

    std::vector<std::vector<int>> g {
      {0, 0},
      {2, 5},
      {1, 3},
      {2, 4},
      {3, 5},
      {2, 5},
    };

    CHECK(countEvenCycles(g, 1) == 1);
  }

  SUBCASE("Inverted home") {
    std::cout << " [Inverted home]";

    std::vector<std::vector<int>> g {
      {0, 0},
      {2, 3},
      {1, 3, 4},
      {1, 2, 5},
      {2, 5, 6},
      {3, 4, 6},
      {4, 5},
    };

    CHECK(countEvenCycles(g, 1) == 2);
  }

  SUBCASE("Pentagon and triangle") {
    std::cout << " [Pentagon and triangle]";

    std::vector<std::vector<int>> g {
      {0, 0},
      {2, 3},
      {1, 4},
      {1, 5},
      {2, 5, 6},
      {3, 4, 6},
      {4, 5},
    };

    CHECK(countEvenCycles(g, 1) == 1);
  }
 
  SUBCASE("Bowtie") {
    std::cout << " [Bowtie]";

    std::vector<std::vector<int>> g {
      {0, 0},
      {2, 3},
      {1, 3},
      {1, 2, 4, 5},
      {3, 5},
      {3, 4},
    };

    CHECK(countEvenCycles(g, 1) == 2);
  }

  SUBCASE("Rocket") {
    std::cout << " [Rocket]";

    std::vector<std::vector<int>> g {
      {0, 0},
      {2, 3},
      {1, 4},
      {1, 4, 5},
      {2, 3, 6},
      {3, 7},
      {4, 7},
      {5, 6},
    };

    CHECK(countEvenCycles(g, 1) == 1);
  }

  std::cout << "\n";
}
