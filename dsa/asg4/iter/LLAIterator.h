#ifndef LLA_IT_H
#define LLA_IT_H

#include "../lla/LinkedListArray.h"

template <class U> class LLA;

template <class T>
class LLAIterator {
private:
  const LLA<T>& c;
  int it;
public:

  // Constructor
  // O(1)
  LLAIterator(const LLA<T>& list): c{list} {
    this->it = 0;
  }


  // Iterate forward
  // O(1)
  void next() {
    if(!this->valid()) throw std::exception();

    this->it++;
  }


  // Iterate backwards
  // O(1)
  void before() {
    if(!this->valid()) throw std::exception();

    this->it--;
  }


  void first() {
    this->it = 0;
  }


  // Get current element
  // O(1)
  T getCurrent() const {
    if(!this->valid()) throw std::exception();

    return this->c.get(this->it);
  }


  // Check valid
  // O(1)
  bool valid() const {
    return this->it >= 0 && this->it < this->c.size;
  }


  // Get iterator idx
  // O(1)
  int getIdx() const {
    return this->it;
  }
};

#endif
