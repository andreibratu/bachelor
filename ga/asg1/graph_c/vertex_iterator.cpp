#include <vector>
#include "vertex_iterator.h"
#include <exception>

VertexIterator::VertexIterator(const std::vector<int>& c): c{c} {
  this->it = this->c.begin();
}

void VertexIterator::first() {
  this->it = this->c.begin();
}

bool VertexIterator::valid() const {
  return this->it != this->c.end();
}

int VertexIterator::getCurrent() const {
  if(this->valid()) {
    return *this->it;
  }
  else throw std::exception();
}

void VertexIterator::next() {
  this->it++;
}
