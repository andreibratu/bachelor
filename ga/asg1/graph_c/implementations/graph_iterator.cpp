#include "../interfaces/graph_iterator.h"

GraphIterator::GraphIterator(const std::vector<Vertex>& c): c{c} {
  this->it = this->c.begin();
}

void GraphIterator::first() {
  this->it = this->c.begin();
}

bool GraphIterator::valid() const {
  return this->it != this->c.end();
}

Vertex GraphIterator::getCurrent() const {
  if(this->valid()) {
    return *this->it;
  }
  else throw std::exception();
}

void GraphIterator::next() {
  this->it++;
}
