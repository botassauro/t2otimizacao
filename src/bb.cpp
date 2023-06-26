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

void mark_cycles_edges_as_counted(int u, int v, int ancestor_u, int ancestor_v) {
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

int countEvenCycles(std::vector<std::vector<int>> g, int u) {
  int cycles = 0;
  q.push(u);

  fill(ancestor.begin(), ancestor.end(), 0);
  fill(state.begin(), state.end(), NOT_PROCESSED);
  fill(distance.begin(), distance.end(), 0);
  edges_counted.clear();

  while ( !q.empty() ) {
    u = q.front();
    q.pop();

    for ( int v : g[u] ) {
      int x, y, node_cnt;
      switch ( state[v] ) {
        case NOT_PROCESSED:
          ancestor[v] = u;
          distance[v] = distance[u] + 1;
          state[v] = IN_QUEUE;
          q.push(v);
          break;

        case IN_QUEUE:
          node_cnt = 2;
          x = u;
          y = v;
          while( ancestor[x] != ancestor[y] &&
            find(g[x].begin(), g[x].end(), ancestor[y]) == g[x].end() &&
            find(g[y].begin(), g[y].end(), ancestor[x]) == g[y].end() &&
            find(g[ancestor[x]].begin(), g[ancestor[x]].end(), ancestor[y]) == g[ancestor[x]].end() ) 
          {
            if ( 
              find(edges_counted.begin(), edges_counted.end(), std::unordered_set<int>{x, ancestor[x]}) != edges_counted.end() || 
              find(edges_counted.begin(), edges_counted.end(), std::unordered_set<int> {y, ancestor[y]}) != edges_counted.end() ) {
                node_cnt = 0;
                break;
              }

            if ( distance[x] < distance[y] ) {
              x = ancestor[x];
              node_cnt++;
            }
            else if ( distance[y] < distance[x] ) {
              y = ancestor[y];
              node_cnt++;
            }
            else {
              x = ancestor[x];
              y = ancestor[y];
              node_cnt += 2;
            }
          }

          if ( ancestor[x] == ancestor[y] ) {
            node_cnt++;  
          }
          else {
            if ( find(g[x].begin(), g[x].end(), ancestor[y]) != g[x].end() ) {
              if ( find(edges_counted.begin(), edges_counted.end(), std::unordered_set{x, ancestor[y]}) == edges_counted.end() ) {
                node_cnt++;
              }
              else {
                node_cnt = 0;
              }
            }
            else {
              if ( find(g[y].begin(), g[y].end(), ancestor[x]) != g[y].end() ) {
                if ( find(edges_counted.begin(), edges_counted.end(), std::unordered_set{y, ancestor[x]}) == edges_counted.end() ) {
                  node_cnt++;
                }
                else {
                  node_cnt = 0;
                }
              }
              else {
                if ( find(edges_counted.begin(), edges_counted.end(), std::unordered_set{ancestor[y], ancestor[x]}) != edges_counted.end() ) {
                  node_cnt = 0;
                }

                node_cnt+=2;
              }
            }
          }

          if ( node_cnt % 2 == 1 ) {
            cycles++;
            mark_cycles_edges_as_counted(u, v, ancestor[x], ancestor[y]);
          }
          break;

        case PROCESSED:
          break;
      }
    }

    state[u] = PROCESSED;
  }

  return cycles;
}

