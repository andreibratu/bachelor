#include "MatrixIterator.h"
#include "../dll/DLL.h"
#include <exception>

MatrixIterator::MatrixIterator(DLLIterator<Record> it): list_it{it} {}

bool MatrixIterator::valid() const {
  return this->list_it.valid();
}


int MatrixIterator::getCurrent() const {
  if(!this->list_it.valid()) throw std::exception();
  return this->list_it.get()->val.val;
}


void MatrixIterator::next() {
  if(!this->list_it.valid()) throw std::exception();
  this->list_it.forward();
}
