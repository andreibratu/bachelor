#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include "vertex.h"
#include "iterator.h"


template <class T>
class Graph {
private:
  typedef std::pair<T,T> Edge;
  std::vector<Vertex<T>> vertices;
  std::unordered_map<Edge, int, boost::hash<Edge>> edges;
  typename std::vector<Vertex<T>>::iterator find_vertex(T label);
public:
  Graph();

  bool is_edge(T, T) const;

  bool add_vertex(T);

  bool remove_vertex(T);

  bool add_edge(T, T);

  bool remove_edge(T, T);

  int size();

  Iterator<Vertex<T>> get_graph_iterator() const;

  int get_edge_property(T, T);

  void set_edge_property(T, T, int);
};

template class Graph<int>;

#endif
