#ifndef GRAPH_IT_H
#define GRAPH_IT_H

#include <vector>
#include "vertex.h"

class Vertex;
class Graph;

class GraphIterator {
private:
  const std::vector<Vertex> c;
  std::vector<Vertex>::const_iterator it;
public:
  GraphIterator(const std::vector<Vertex>& c);

  void first();

  bool valid() const;

  Vertex getCurrent() const;

  void next();
};

#endif
