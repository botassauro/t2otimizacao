#include <queue>
#include <algorithm>
#include <iostream>
#include "limiting-function.h"

#define COUNTED 1

#define NOT_PROCESSED 0
#define IN_QUEUE 1
#define PROCESSED 2

void CountCycles::markCyclesEdgesAsCounted(int u, int v, int ancestor_u, int ancestor_v) {
  edges_counted[u][v] = COUNTED;
  edges_counted[v][u] = COUNTED;

  if ( ancestor_u != ancestor_v ) { 
    edges_counted[ancestor[u]][ancestor[v]] = COUNTED;
    edges_counted[ancestor[v]][ancestor[u]] = COUNTED;
  }

  for ( ; u != ancestor_u; u = ancestor[u] ) {
    edges_counted[u][ancestor[u]] = COUNTED;
    edges_counted[ancestor[u]][u] = COUNTED;
  }

  for ( ; v != ancestor_v; v = ancestor[v] ) {
    edges_counted[v][ancestor[v]] = COUNTED;
    edges_counted[ancestor[v]][v] = COUNTED;
  }
}

void CountCycles::addVertexToQueue(int u, int v) {
  ancestor[v] = u;
  distance[v] = distance[u] + 1;
  state[v] = IN_QUEUE;
  q.push(v);
}

bool areTheSameVertex(int x, int y) {
  return x == y;
}

bool areVerticesNeighbors(std::vector<int> x , int y) {
  return find(x.begin(), x.end(), y) != x.end();
}

bool CountCycles::hasCycleClosed(int x, int y) {
  if ( areTheSameVertex(ancestor[x], ancestor[y]) ) {
    return true;
  }

  if ( areVerticesNeighbors(g[x], ancestor[y]) ) {
    return true;
  }

  if ( areVerticesNeighbors(g[y], ancestor[x]) ) {
    return true;
  }

  if ( areVerticesNeighbors(g[ancestor[x]], ancestor[y]) ) {
    return true;
  }

  return false;
}

bool CountCycles::isEdgeInAnotherCycle(int x, int y) {
  return edges_counted[x][y] == COUNTED || edges_counted[y][x] == COUNTED;
}

int CountCycles::walkVertices(int& x, int& y) {
  int walk_amount = 0;

  int disX = distance[x];
  int disY = distance[y];
  //std::cout << disX << " " << disY << "\n";

  if ( disX <= disY ) {
    y = ancestor[y];
    walk_amount++;
  }

  if ( disY <= disX ) {
    x = ancestor[x];
    walk_amount++;
  }

  return walk_amount;
}

int CountCycles::findCycle(int& x, int& y) {
  int vertices_walked = 0;

  while ( hasCycleClosed(x, y) == false ) {
    if ( isEdgeInAnotherCycle(x, ancestor[x]) ) {
      return 0;
    }

    if ( isEdgeInAnotherCycle(y, ancestor[y]) ) {
      return 0;
    }

    vertices_walked += walkVertices(x, y);
  }

  return vertices_walked;
}

int CountCycles::walkToCommonAncestor(int x, int y) {
  int vertices_walked = findCycle(x, y);

  if ( areVerticesNeighbors(g[x], ancestor[y]) ) {
    return isEdgeInAnotherCycle(x, ancestor[y]) ? 0 : vertices_walked + 1;
  }

  if ( areVerticesNeighbors(g[y], ancestor[x]) ) {
    return isEdgeInAnotherCycle(y, ancestor[x]) ? 0 : vertices_walked + 1;
  }

  if ( areVerticesNeighbors(g[ancestor[x]], ancestor[y]) ) {
    return isEdgeInAnotherCycle(ancestor[x], ancestor[y]) ? 0 : vertices_walked + 2;
  }

  // They have the same vertex
  return vertices_walked + 1;
}

bool CountCycles::processCycle(int u, int v) {
  int u_start = u;
  int v_start = v;

  int vertices_until_common_ancestor = walkToCommonAncestor(u, v);
  int vertices_in_cycle = vertices_until_common_ancestor + 2;

  if ( compFunc(vertices_in_cycle) ) {
    markCyclesEdgesAsCounted(u_start, v_start, ancestor[u], ancestor[v]);
    return true;
  }

  return false;
}

bool CountCycles::processNeighbor(int u, int v) {
  switch ( state[v] ) {
    case NOT_PROCESSED:
      addVertexToQueue(u, v);
      return 0;

    case IN_QUEUE:
      return processCycle(u, v);

    case PROCESSED:
      return 0;
  }

  return 0;
}

int CountCycles::vertexNewCyclesAmount(int u) {
  int new_cycles = 0;

  for ( int v : g[u] ) {
    new_cycles += processNeighbor(u, v) ? 1 : 0;
  }

  return new_cycles;
}

int CountCycles::findFirstNeighbor() {
  for ( size_t u = 1; u < g.size(); u++ ) {
    if ( state[u] == NOT_PROCESSED)
      return u;
  }

  return 1;
}

bool CountCycles::hasVisitedAllVertices() {
  for ( size_t u = 1; u < g.size(); u++ ) {
    for ( int v : g[u] ) {
      if ( state[v] != PROCESSED )
        return false;
    }
  }

  return true;
}

int CountCycles::countCycles() {
  int cycles = 0;

  do {
    int first = findFirstNeighbor();
    q.push(first);

    while ( !q.empty() ) {
      int u = q.front();
      q.pop();
      cycles += vertexNewCyclesAmount(u);
      state[u] = PROCESSED;
    }

  } while ( hasVisitedAllVertices() == false );

  return cycles;
}

bool isEven(int cnt) {
  
  return cnt % 2 == 1;
}

int CountCycles::countEvenCycles() {
  compFunc = isEven;
  return countCycles();
}

bool isTriangle(int cnt) {
  
  return cnt == 3;
}

int CountCycles::countTriangles() {
  compFunc = isTriangle;
  return countCycles();
}

CountCycles::CountCycles(std::vector<std::vector<int>> g) 
  : g(g), ancestor(g.size()+1), state(g.size()+1), distance(g.size()+1), edges_counted(g.size()+1, std::vector<int>(g.size()+1)) {
}

int limitingFunction(std::vector<std::vector<int>> conflicts, int conflicts_choosen, bool countTriangles) {
  CountCycles cc(conflicts);
  if ( countTriangles ) {
    return cc.countTriangles() + conflicts_choosen;
  }
    
  int cnt = cc.countEvenCycles() + conflicts_choosen;
  return cnt;
}

