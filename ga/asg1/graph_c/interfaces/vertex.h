#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "vertex_iterator.h"

template <class T>
class VertexIterator;


template <class T>
class Vertex {
private:
  std::vector<T> inbound;
  std::vector<T> outbound;
public:
  T label;

  Vertex(T);

  int get_degree_in(void) const;

  int get_degree_out(void) const;

  bool add_inbound(T);

  bool add_outbound(T);

  VertexIterator<T> get_inbound_edges_iterator() const;

  VertexIterator<T> get_outbound_edges_iterator() const;

  void remove_inbound(T);

  void remove_outbound(T);
};

#endif
