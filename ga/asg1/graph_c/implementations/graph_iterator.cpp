#include "../interfaces/graph_iterator.h"


template <class T>
GraphIterator<T>::GraphIterator(const std::vector<Vertex<T>>& c): c{c} {
  this->it = this->c.begin();
}


template <class T>
void GraphIterator<T>::first() {
  this->it = this->c.begin();
}


template <class T>
bool GraphIterator<T>::valid() const {
  return this->it != this->c.end();
}


template <class T>
Vertex<T> GraphIterator<T>::getCurrent() const {
  if(this->valid()) {
    return *this->it;
  }
  else throw std::exception();
}


template <class T>
void GraphIterator<T>::next() {
  this->it++;
}


template class GraphIterator<int>;
