#ifndef __BB__
#define __BB__

#include <queue>
#include <vector>

class CountCycles {
private:
  std::vector<std::vector<int>> g;
  std::queue<int> q;
  std::vector<int> ancestor;
  std::vector<int> state;
  std::vector<int> distance;
  std::vector<std::vector<int>> edges_counted;

  bool (*compFunc)(int cnt);

  int vertexNewCyclesAmount(int u);
  bool processNeighbor(int u, int v);
  void addVertexToQueue(int u, int v);

  void markCyclesEdgesAsCounted(int u, int v, int ancestor_u, int ancestor_v);
  int walkVertices(int& x, int& y);
  int findCycle(int& x, int& y);
  int walkToCommonAncestor(int x, int y);
  bool processCycle(int u, int v);
  bool hasCycleClosed(int x, int y);
  bool isEdgeInAnotherCycle(int x, int y);
  int countCycles();

public:
  int countEvenCycles();
  int countTriangles();
  CountCycles(std::vector<std::vector<int>> g);
};

int limitingFunction(std::vector<std::vector<int>> conflicts, int conflicts_choosen, bool countTriangles);

#endif
