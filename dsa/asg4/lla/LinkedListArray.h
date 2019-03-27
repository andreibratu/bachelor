#ifndef LLA_H
#define LLA_H

#include <string.h>
#include <exception>
#include "../iter/LLAIterator.h"


template <class U> class LLAIterator;


template <class T>
class LLA {

template <class U> friend class LLAIterator;

private:
  T* head;
  int size;
  int capacity;

  // O(N), container elements must be moved to new array
  // Throws if `newCap` smaller than current number of elements
  void resize(int newCap) {
    if(newCap <= this->size) throw std::exception();
    T* nArr = new T [newCap];
    memcpy(nArr, this->head, this->size*sizeof(T));
    delete[] this->head;
    this->head = nArr;
    this->capacity = newCap;
  }

public:

  // Constructor
  // O(1)
  LLA() {
    this->capacity = 1;
    this->size = 0;
    this->head = new T [this->capacity];
  }


  // Insert element before given idx
  // O(N), linear with how many elements are moved
  // Resizing may happen
  void addBefore(int idx, T e) {
    if(this->size == this->capacity) this->resize(this->capacity*2);

    memcpy(this->head+idx+1, this->head+idx, (this->size-idx+1)*sizeof(T));
    this->head[idx] = e;
    this->size++;
  }


  // Delete element on given index
  // O(N), linear with how many elements are moved
  void remove(int idx) {
    memcpy(this->head+idx, this->head+idx+1, (this->size-idx)*sizeof(T));
    this->size--;
    if(this->size < this->capacity/4) this->resize(this->capacity/2);
  }


  // Get element by index
  // O(1)
  T get(int idx) const {
    return this->head[idx];
  }


  // Insert element at container end
  // Amortised O(1), resize might be necessary
  void insert(T e) {
    if(this->size == this->capacity) this->resize(this->capacity*2);
    this->head[size++] = e;
  }


  // Return iterator
  // O(1)
  LLAIterator<T> getIterator() const {
    return LLAIterator<T>(*this);
  }


  // Get LLA size
  // O(1)
  int getSize() const {
    return this->size;
  }


  // Destructor
  ~LLA() {
    delete[] head;
  }
};

#endif
