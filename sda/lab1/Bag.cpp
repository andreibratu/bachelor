//DSA7642
#include "Bag.h"
#include "BagIterator.h"
#include <string.h>

Bag::Bag() {
    this->allocated_size = 1;
    this->logical_size = 0;
    this->total_elements = 0;
    this->array = new Pair [this->allocated_size];
}

void Bag::add(TElem e) {
    for(int i = 0; i < this->logical_size; i++) {
        if(e == this->array[i].element) {
            this->array[i].apparitions += 1;
            this->total_elements += 1;
            return;
        }
    }

    if(this->logical_size == this->allocated_size) {
      // Reallocation is necessary
      this->allocated_size *= 2;
      Pair* newArray = new Pair [this->allocated_size];
      memcpy(newArray, this->array, this->logical_size * sizeof(Pair));
      delete[] this->array;
      this->array = newArray;
    }
    this->array[this->logical_size].element = e;
    this->array[this->logical_size].apparitions = 1;
    this->logical_size += 1;
    this->total_elements += 1;
}

bool Bag::remove(TElem e) {
    if(!this->search(e)) return false;
    else {
        for(int i=0; i<this->logical_size; i++) {
            if(this->array[i].element == e) {
                this->array[i].apparitions -= 1;
                this->total_elements -= 1;
                return true;
            }
        }
    }
}

bool Bag::search(TElem e) const {
    for(int i=0; i<this->logical_size; i++) {
        if(this->array[i].element == e && this->array[i].apparitions > 0) {
            return true;
        }
    }
    return false;
}

int Bag::nrOccurrences(TElem e) const {
    if(!this->search(e)) return 0;
    else {
        for(int i=0; i<this->logical_size; i++) {
            if(this->array[i].element == e) {
                return this->array[i].apparitions;
            }
        }
    }
}

int Bag::size() const {
    return this->total_elements;
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
