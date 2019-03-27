#include "BagIterator.h"
#include "Bag.h"
#include <exception>
#include <iostream>


// Constant members of the class should be init like this
// O(1)
BagIterator::BagIterator(const Bag& c): c{c} {
    this->idx = 0;
}


// O(1)
void BagIterator::first() {
    this->idx = 0;
}


// O(1)
void BagIterator::next() {
  this->idx++;
}


// O(1)
bool BagIterator::valid() const {
  return this->idx < this->c.size();
}


// O(1)
TElem BagIterator::getCurrent() const {
  if(this->valid()) {
    return this->c.array[this->idx];
  }
  else throw std::exception();
}
