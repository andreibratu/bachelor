#ifndef DLL_IT_H
#define DLL_IT_H

#include "../Node.h"
#include "../dll/DLL.h"

template <class U> class DLL;

template <class T>
class DLLIterator {
private:
  const DLL<T>& c;
  Node<T>* it;
public:
  // Constructor
  // O(1)
  DLLIterator(const DLL<T>& list): c{list} {
    this->it = list.head;
  }

  // Iterator does not point to null
  // O(1)
  bool valid() const {
    return this->it != 0;
  }

  // `next` node is not NULL
  // O(1)
  bool peekFront() const {
    return this->it->next != 0;
  }

  // `before` node is not NULL
  // O(1)
  bool peekBack() const {
    return this->it->before != 0;
  }

  // Get current Node*
  // O(1)
  Node<T>* get() const {
    return this->it;
  }

  // Move iterator forward
  // O(1)
  void forward() {
    this->it = this->it->next;
  }

  // Move iterator backwards
  // O(1)
  void backwards() {
    this->it = this->it->before;
  }
};

#endif
