#include <vector>
#include "../interfaces/vertex_iterator.h"
#include <exception>


template <class T>
VertexIterator<T>::VertexIterator(const std::vector<T>& c): c{c} {
  this->it = this->c.begin();
}


template <class T>
void VertexIterator<T>::first() {
  this->it = this->c.begin();
}


template <class T>
bool VertexIterator<T>::valid() const {
  return this->it != this->c.end();
}

template <class T>
T VertexIterator<T>::getCurrent() const {
  if(this->valid()) {
    return *this->it;
  }
  else throw std::exception();
}

template <class T>
void VertexIterator<T>::next() {
  this->it++;
}

template class VertexIterator<int>;
