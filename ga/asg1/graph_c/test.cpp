#include <stdio.h>
#include "interfaces/graph.h"
#include "interfaces/generator.h"


int main() {
  // Create graph
  Graph g = Graph();

  // Add vertices
  for(int i=0; i<100 ;i++) g.add_vertex(i);

  // Remove vertices
  assert(g.size() == 100);
  g.add_edge(5, 6);
  g.remove_vertex(5);
  assert(!g.remove_edge(5, 6));
  assert(g.size() == 99);
  Iterator<Vertex> it0 = g.get_graph_iterator();
  for(; it0.valid(); it0.next()) {
    assert(it0.getCurrent().label != 100);
  }

  g.remove_vertex(6);
  assert(g.size() == 98);
  assert(!g.remove_vertex(99));

  // Edge iterator
  g.add_edge(3, 1);
  g.add_edge(3, 11);
  Iterator<int> it1 = g.get_outbound_edges_it(3);
  int i = 0;
  for(; it1.valid(); i++, it1.next());
  assert(i == 2);
  i = 0;
  Iterator<int> it2 = g.get_inbound_edges_it(1);
  for(; it2.valid(); i++, it2.next());

  // Edges are directed
  assert(!g.is_edge(1, 3));
  assert(g.is_edge(3, 1));
  g.add_edge(1, 3);

  // Setting propery of non existent edges throws
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
  // Cannot remove non-existent edge
  assert(g.remove_edge(1, 3));
  assert(g.remove_edge(3, 1));
  assert(!g.remove_edge(1, 3));
  Graph g1 = generate_random_graph(40, 8);

  // Copy a graph
  Graph g2 = g1;
  g2.add_vertex(567);
  g2.add_edge(4, 1);
  try {
    g1.get_edge_property(4, 1);
    assert(false);
  }
  catch(std::exception) {}
  assert(!g1.remove_vertex(567));
  return 0;
}
