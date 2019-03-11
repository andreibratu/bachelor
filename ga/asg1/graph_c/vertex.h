#pragma once

#include <vector>
#include "vertex_iterator.h"

class VertexIterator;

class Vertex {
private:
  std::vector<int> inbound;
  std::vector<int> outbound;
public:
  int label;
  
  Vertex(int);

  int get_degree_in(void) const;

  int get_degree_out(void) const;

  bool add_inbound(int);

  bool add_outbound(int);

  VertexIterator parse_inbound_edges() const;

  VertexIterator parse_outbound_edges() const;

  void remove_inbound(int);

  void remove_outbound(int);
};
