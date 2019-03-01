//DSA7642
#include "Bag.h"
#include "BagIterator.h"
#include <string.h>

Bag::Bag() {
    this->capacity = 1;
    this->logical_size = 0;
    this->array = new TElem [this->capacity];
}

void Bag::add(TElem e) {
    if(this->logical_size == this->capacity) {
      // Reallocation is necessary
      this->capacity *= 2;
      TElem* newArray = new TElem [this->capacity];
      memcpy(newArray, this->array, this->size() * sizeof(TElem));
      delete[] this->array;
      this->array = newArray;
    }
    this->array[this->logical_size++] = e;
}

bool Bag::remove(TElem e) {
  for(int i=0; i<this->size(); i++) {
    if(this->array[i] == e) {
      // Move all elements after index i to the left by one position
      int how_many_to_move = this->size()-i-1;
      memcpy(this->array+i, this->array+i+1, how_many_to_move*sizeof(TElem));
      this->logical_size -= 1;
      return true;
    }
  }
  return false;
}

bool Bag::search(TElem e) const {
  for(int i=0; i<this->logical_size; i++) {
      if(this->array[i] == e) {
          return true;
      }
  }
  return false;
}

int Bag::nrOccurrences(TElem e) const {
  int counter = 0;
  for(int i=0; i<this->size(); i++) {
    if(this->array[i] == e) counter++;
  }
  return counter;
}

int Bag::size() const {
  return this->logical_size;
}

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}

bool Bag::isEmpty() const {
    return this->logical_size == 0;
}

Bag::~Bag() {
    delete[] this->array;
}
