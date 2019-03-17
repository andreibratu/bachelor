#include "interfaces/graph.h"

int main() {
  Graph<int> g = Graph<int>();
  g.add_vertex(3);
  g.add_vertex(1);
  g.add_vertex(6);
  g.add_vertex(11);
  assert(g.size() == 4);
  g.remove_vertex(5);
  assert(g.size() == 4);
  g.remove_vertex(6);
  assert(g.size() == 3);
  assert(!g.add_edge(34, 35));
  g.add_edge(3, 1);
  assert(!g.is_edge(1, 3));
  assert(g.is_edge(3, 1));
  g.add_edge(1, 3);
  try {
    g.get_edge_property(67, 13);
    assert(false);
  }
  catch(std::exception) {}
  try {
    g.set_edge_property(111, 122, 4);
    assert(false);
  }
  catch(std::exception) {}
  assert(g.remove_edge(1, 3));
  assert(g.remove_edge(3, 1));
  assert(!g.remove_edge(1, 3));
  return 0;
}
