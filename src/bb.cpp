#include <queue>
#include <algorithm>
#include <unordered_set>

#define NOT_PROCESSED 0
#define IN_QUEUE 1
#define PROCESSED 2

std::vector<int> state(15);
std::vector<int> ancestor(15);
std::vector<int> distance(15);
std::queue<int> q;
std::vector<std::unordered_set<int>> edges_counted;

void markCyclesEdgesAsCounted(int u, int v, int ancestor_u, int ancestor_v) {
  edges_counted.push_back(std::unordered_set{u, v});
  if ( ancestor_u != ancestor_v ) { 
    edges_counted.push_back(std::unordered_set{ancestor_u, ancestor_v});
  }

  for ( ; u != ancestor_u; u = ancestor[u] ) {
    edges_counted.push_back(std::unordered_set{u, ancestor_u});
  }

  for ( ; v != ancestor_v; v = ancestor[v] ) {
    edges_counted.push_back(std::unordered_set{v, ancestor_v});
  }
}

void addVertexToQueue(int u, int v) {
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

bool hasCycleClosed(std::vector<std::vector<int>> g, int x, int y) {
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

bool isEdgeInAnotherCycle(int x, int y) {
  return find(edges_counted.begin(), edges_counted.end(), std::unordered_set<int>{x, y}) != edges_counted.end();
}

int walkVertices(int& x, int& y) {
  int walk_amount = 0;

  int disX = distance[x];
  int disY = distance[y];

  if ( disX <= disY ) {
    x = ancestor[x];
    walk_amount++;
  }

  if ( disY <= disX ) {
    y = ancestor[y];
    walk_amount++;
  }

  return walk_amount;
}

int findCycle(std::vector<std::vector<int>> g, int& x, int& y) {
  int vertices_walked = 0;

  while ( hasCycleClosed(g, x, y) == false ) {
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

int walkToCommonAncestor(std::vector<std::vector<int>> g, int x, int y) {
  int vertices_walked = findCycle(g, x, y);

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

bool processCycle(std::vector<std::vector<int>> g, int u, int v) {
  int u_start = u;
  int v_start = v;

  int vertices_until_common_ancestor = walkToCommonAncestor(g, u, v);
  int vertices_in_cycle = vertices_until_common_ancestor + 2;

  if ( vertices_in_cycle % 2 == 1 ) {
    markCyclesEdgesAsCounted(u_start, v_start, ancestor[u], ancestor[v]);
    return true;
  }

  return false;
}

bool processNeighbor(std::vector<std::vector<int>> g, int u, int v) {
  switch ( state[v] ) {
    case NOT_PROCESSED:
      addVertexToQueue(u, v);
      return 0;

    case IN_QUEUE:
      return processCycle(g, u, v);

    case PROCESSED:
      return 0;
  }

  return 0;
}

int vertexNewCyclesAmount(std::vector<std::vector<int>> g, int u) {
  int new_cycles = 0;

  for ( int v : g[u] ) {
    new_cycles += processNeighbor(g, u, v) ? 1 : 0;
  }

  return new_cycles;
}

void initVectors() {
  fill(ancestor.begin(), ancestor.end(), 0);
  fill(state.begin(), state.end(), NOT_PROCESSED);
  fill(distance.begin(), distance.end(), 0);
  edges_counted.clear();
}

int countEvenCycles(std::vector<std::vector<int>> g, int u) {
  int cycles = 0;
  initVectors();

  q.push(u);

  while ( !q.empty() ) {
    u = q.front();
    q.pop();
    cycles += vertexNewCyclesAmount(g, u);
    state[u] = PROCESSED;
  }

  return cycles;
}

