#ifndef GRAPH_IT_H
#define GRAPH_IT_H

#include <vector>
#include "vertex.h"

template <class T>
class Vertex;

template <class T>
class Graph;


template <class T>
class GraphIterator {
private:
  const std::vector<Vertex<T>> c;
  typename std::vector<Vertex<T>>::const_iterator it;
public:
  GraphIterator(const std::vector<Vertex<T> >& c);

  void first();

  bool valid() const;

  Vertex<T> getCurrent() const;

  void next();
};

#endif
