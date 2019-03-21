#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include "vertex.h"
#include "iterator.h"


class Graph {
private:
  typedef std::pair<int, int> Edge;
  std::vector<Vertex> vertices;
  std::unordered_map<Edge, int, boost::hash<Edge>> edges;
  std::vector<Vertex>::iterator find_vertex(int);
public:
  Graph();

  bool is_edge(int, int) const;

  bool add_vertex(int);

  bool remove_vertex(int);

  bool add_edge(int, int);

  bool remove_edge(int, int);

  int size();

  Iterator<Vertex> get_graph_iterator() const;

  int get_edge_property(int, int);

  void set_edge_property(int, int, int);
};

#endif
