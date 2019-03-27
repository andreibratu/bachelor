#include <exception>
#include "Matrix.h"


Matrix::Matrix(int nrLines, int nrCols) {
  if(nrLines <= 0 || nrCols <= 0) throw std::exception();
  this->r = nrLines;
  this->c = nrCols;
}


int Matrix::nrLines() const {
  return this->r;
}


int Matrix::nrColumns() const {
  return this->c;
}


TElem Matrix::element(int i, int j) const {
  if(i<0 || i >= this->r || j < 0 || j >= this->c) throw std::exception();

  DLLIterator<Record> it = this->list.getIterator();
  for(; it.valid(); it.forward()) {
    Record r = this->list.get(it.get());
    if(r.row == i && r.col == j) return r.val;
  }

  return NULL_TELEM;
}


TElem Matrix::modify(int i, int j, TElem e) {
  if(i<0 || i >= this->r || j < 0 || j >= this->c) throw std::exception();

  DLLIterator<Record> it = this->list.getIterator();
  for(; it.valid(); it.forward()) {
    Record r = this->list.get(it.get());
    if(r.row < i) continue;
    if(r.row == i) {
      if(r.col < j) continue;
      if(r.col == j) {
        TElem old_val = r.val;
        this->list.update(it.get(), {i, j, e});
        return old_val;
      }
      this->list.insert(it.get(), {i, j, e});
      return NULL_TELEM;
    }
  }

  this->list.insert(0, {i, j, e});
  return NULL_TELEM;
}
