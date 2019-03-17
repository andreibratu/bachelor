#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include "vertex.h"
#include "graph_iterator.h"


template <class T>
class Vertex;


template <class T>
class Graph {
private:
  typedef std::pair<T,T> Edge;
  std::vector<Vertex<T>> vertices;
  std::unordered_map<Edge, int, boost::hash<Edge>> edges;
public:
  Graph();

  bool is_edge(T, T) const;

  bool add_vertex(T);

  bool remove_vertex(T);

  bool add_edge(T, T);

  bool remove_edge(T, T);

  int size();

  GraphIterator<T> get_graph_iterator() const;

  int get_edge_property(T, T);

  void set_edge_property(T, T, int);
};

#endif
