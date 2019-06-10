#include "BFS.h"
#include <iostream>

int main() {
  Graph g;

  for(int i = 1; i <= 6; i++) g.add_vertex(i);
  g.add_edge(1, 2);
  g.add_edge(1, 4);
  g.add_edge(2, 4);
  g.add_edge(2, 3);
  g.add_edge(4, 3);
  g.add_edge(3, 6);
  g.add_edge(4, 5);

  std::vector<int> path = backwardBFS(g, 1, 3);
  assert(path.size() == 3);
  for(auto x: path) {
    std::cout << x << '\n';
  }


  Graph g2 = Graph();
  assert(g2.size() == 0);
  for(int i = 1; i <= 6; i++) g2.add_vertex(i);
  g2.add_edge(1, 4);
  g2.add_edge(5, 6);

  std::vector<int> v2 = backwardBFS(g2, 1, 6);
  assert(v2.size() == 0);

  std::vector<int> v3 = backwardBFS(g2, 1, 1);
  assert(v3.size() == 1);

  return 0;
}
