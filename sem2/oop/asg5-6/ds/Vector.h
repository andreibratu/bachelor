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

  void resize() {
    T* els = new T [this->capacity * 2];
    for (int i = 0; i < this->logicalSize ; i++)
      els[i] = this->array[i];

    this->capacity *= 2;
    delete[] this->array;
    this->array = els;
  }
public:


  Vector() {
    this->logicalSize = 0;
    this->capacity = 1;
    this->array = new T [this->capacity];
  }


  Vector(const Vector& v) {
    logicalSize = v.logicalSize;
    capacity = v.capacity;
    this->array = new T [this->capacity];
    for(int i = 0; i < v.size(); i++) {
      this->array[i] = v.array[i];
    }
  }

  Vector<T>& operator = (const Vector<T>& other) {
    this->logicalSize = other.logicalSize;
    this->capacity = other.capacity;

    delete[] this->array;

    this->array = new T [this->capacity];
    for(int i = 0; i < other.size(); i++) {
      this->array[i] = other.array[i];
    }

    return *this;
  }


  int size() const {
    return this->logicalSize;
  }


  void push_back(T el) {
    if(this->logicalSize == this->capacity) {
      this->resize();
    }
    this->array[this->logicalSize++] = el;
  }


  T& operator [] (int index) const {
    if(index < 0 || index >= this->logicalSize) {
      throw std::exception();
    }

    return this->array[index];
  }


  void remove(int index) {
    if(index < 0 or index >= this->logicalSize) {

      throw std::exception();
    }

    std::copy(this->array+index+1, this->array+logicalSize, this->array+index);

    this->logicalSize--;
  }


  friend std::ostream& operator << (std::ostream& os, const Vector<T>& v) {
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
