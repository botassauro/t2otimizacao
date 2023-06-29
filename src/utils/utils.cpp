#include <vector>
#include <iostream>
#include <iomanip>
#include <sys/time.h>

#include "utils.h"
#include "backtracking.h"
#include "limiting-function.h"

std::vector<std::vector<int>> readGraph(int n, int k) {
  int u, v;
  std::vector<std::vector<int>> graph(n);
  for ( int i = 0; i < k; i++ ) {
    std::cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  return graph;
}

Problem readHeroes() {
  Problem P;

  int n;
  std::cin >> n;
  P.number_of_heroes = n;
  P.g.resize(n+1);
  fill(P.g.begin(), P.g.end(), -1);

  int k, m;
  std::cin >> k >> m;

  P.conflicts_cnt = 0;
  P.conflicts = readGraph(n+1, k);
  P.affinities = readGraph(n+1, m);
  
  return P;
}

void printSolution(std::vector<int> S, int min, int nodes, double t) {
  std::cout << min << "\n";
  std::cout << 1;
  for ( size_t i = 2; i < S.size(); i++ ) {
    if ( S[i] == S[1] ) {
      std::cout << " " << i;
    }
  }

  std::cout << "\n";

  std::cerr << "Quantidades de nodos: " << nodes << "\n";
  std::cerr << "Tempo: " << std::fixed << std::setprecision(4) << t << "\n";
}

double timestamp() {
  struct timeval now;
  gettimeofday(&now, 0);
  long seconds = now.tv_sec;
  long microseconds = now.tv_usec;
  return seconds + microseconds * 1e-6;
}
