#include "BFS.h"
#include <algorithm>
#include <queue>

std::vector<int> backwardBFS(Graph& g, int source, int dest) {
  if(source == dest) return std::vector<int>{};

  std::queue<int> Q;
  std::vector<bool> seen(g.size());
  std::vector<int> parent(g.size());
  std::vector<int> solution;

  Q.push(dest);
  parent[dest] = -1;

  while(Q.size()) {
    int currNode = Q.front();
    Q.pop();
    seen[currNode] = 1;
    Iterator<int> it = g.get_inbound_edges_it(currNode);
    while(it.valid()) {
      int formerNode = it.getCurrent();
      if(!seen[formerNode]) {
        parent[formerNode] = currNode;
        Q.push(currNode);
      }
    }
  }

  int aux = source;
  while(parent[aux] != -1) {
    solution.push_back(aux);
    aux = parent[aux];
  }

  return solution;
}
