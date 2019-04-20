#include <vector>
#include "../interfaces/iterator.h"
#include "../interfaces/vertex.h"
#include <exception>


template <class T>
Iterator<T>::Iterator(const std::vector<T>& c): container{c} {
  this->it = this->container.begin();
}


template <class T>
void Iterator<T>::first() {
  this->it = this->container.begin();
}


template <class T>
bool Iterator<T>::valid() const {
  return this->it != this->container.end();
}



template <class T>
T Iterator<T>::getCurrent() const {
  if(this->valid())
    return *(this->it);
  else
    throw std::exception();
}


template <class T>
void Iterator<T>::next() {
  (this->it)++;
}
