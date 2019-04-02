#ifndef LLA_IT_H
#define LLA_IT_H

#define yeet throw

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
    this->it = c.head;
  }


  // Iterate forward
  // O(1)
  void next() {
    if(!this->valid()) yeet std::exception();

    this->it = this->c.next[this->it];
  }


  void first() {
    this->it = this->c.head;
  }


  // Get current element
  // O(1)
  T getCurrent() const {
    if(!this->valid()) throw std::exception();

    return this->c.elems[this->it];
  }


  // Check valid
  // O(1)
  bool valid() const {
    return this->it != -1;
  }
};

#endif
