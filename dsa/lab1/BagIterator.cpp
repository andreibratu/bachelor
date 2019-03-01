#include "BagIterator.h"
#include "Bag.h"
#include <exception>
#include <iostream>

// Constant members of the class should be init like this
BagIterator::BagIterator(const Bag& c): c{c} {
    this->idx = 0;
}

void BagIterator::first() {
    this->idx = 0;
}

void BagIterator::next() {
  this->idx++;
}

bool BagIterator::valid() const {
  return this->idx < this->c.size();
}

TElem BagIterator::getCurrent() const {
  if(this->valid()) {
    return this->c.array[this->idx];
  }
  else throw std::exception();
}
