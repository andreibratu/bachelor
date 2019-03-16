#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <unordered_set>
#include <boost/functional/hash.hpp>
#include "vertex.h"
#include "graph_iterator.h"

typedef std::pair<int,int> Edge;

class Graph {
private:
  std::vector<Vertex> vertices;
  std::unordered_set<Edge, int, boost::hash<Edge>> edges;
public:
  Graph();

  bool is_edge(int, int) const;

  bool add_vertex(int);

  bool remove_vertex(int);

  bool add_edge(int, int);

  bool remove_edge(int, int);

  int size();

  GraphIterator get_graph_iterator() const;

  int get_edge_property(int, int) const;

  void set_edge_property(int, int, int);
};

#endif
