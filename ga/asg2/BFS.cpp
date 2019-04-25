#include "BFS.h"
#include <algorithm>
#include <queue>

std::vector<int> backwardBFS(Graph& g, int source, int dest) {
  if(source == dest) return std::vector<int>{source};

  std::queue<int> Q;
  std::vector<bool> seen(g.size(), false);
  std::vector<int> successor(g.size(), -1);
  std::vector<int> solution;

  Q.push(dest);
  seen[dest] = true;

  while(!Q.empty()) {
    int currNode = Q.front();
    Q.pop();
    Iterator<int> it = g.get_inbound_edges_it(currNode);
    while(it.valid()) {
      int formerNode = it.getCurrent();
      if(!seen[formerNode]) {
        seen[formerNode] = true;
        successor[formerNode] = currNode;
        Q.push(formerNode);
      }
      it.next();
    }
  }

  if(successor[source] == -1) {
      // No path exists
      return solution;
  }

  int aux = source;
  while(successor[aux] != -1) {
    solution.push_back(aux);
    aux = successor[aux];
  }
  solution.push_back(aux);

  return solution;
}
