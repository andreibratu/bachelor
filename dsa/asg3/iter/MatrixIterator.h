#ifndef MATRIX_IT_H
#define MATRIX_IT_H
#include "DLLIterator.h"
#include "../Record.h"

class MatrixIterator {
private:
  DLLIterator<Record> list_it;
public:
  MatrixIterator(DLLIterator<Record> it);

  bool valid() const;

  int getCurrent() const;

  void next();
};
#endif
