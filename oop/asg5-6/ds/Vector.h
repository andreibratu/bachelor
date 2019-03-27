#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
#include <string.h>
#include <exception>
#include <iostream>


template <class T>
class Vector {
private:
  int logicalSize;
  int capacity;
  T* array;
public:


  Vector() {
    this->logicalSize = 0;
    this->capacity = 1;
    this->array = new T [this->capacity];
  }


  Vector(const Vector& v) {
    this->logicalSize = 0;
    this->capacity = 1;
    this->array = new T [this->capacity];
    for(int i=0; i<v.size(); i++) {
      this->push_back(T(v[i]));
    }
  }


  void push_back(T el) {
    if(this->logicalSize == this->capacity) {
      T* aux = new T [2*capacity];
      delete[] this->array;
      this->array = aux;
      this->capacity *= 2;
    }
    this->array[this->logicalSize++] = el;
  }


  T& operator [] (int index) const {
    if(index < 0 || index >= this->logicalSize) {
      throw std::exception();
    }

    return this->array[index];
  }


  int find(const T key) const {
    for(int i=0; i<this->logicalSize; i++)
      if(this->array[i] == key)
        return i;

    return -1;
  }

  int size() const {
    return this->logicalSize;
  }


  void remove(int index) {
    if(index < 0 or index >= this->logicalSize) {
      throw std::exception();
    }

    memcpy(
      this->array+index,
      this->array+index+1,
      (this->logicalSize-index+1) * sizeof(T)
    );

    this->logicalSize--;
  }


  template <class U>
  friend std::ostream& operator << (std::ostream& os, const Vector<U>& v) {
    for(int i=0; i<v.size(); i++) {
      os << i << ".   " << v[i] << '\n';
    }

    return os;
  }


  ~Vector() {
    delete[] this->array;
  }
};

#endif
