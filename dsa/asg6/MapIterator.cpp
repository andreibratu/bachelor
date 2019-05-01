//
// Created by andreib on 27.04.2019.
//

#include "MapIterator.h"

MapIterator::MapIterator(const Map& c): map{c} {
    this->first();
}

void MapIterator::first() {
    this->idx = 0;
    while(this->map.hashTable.array[this->idx].first == -1) {
        this->idx++;
    }
}

void MapIterator::next() {
    if(!this->valid()) throw std::exception();
    while(this->map.hashTable.array[this->idx].first == -1) {
        this->idx++;
    }
}

bool MapIterator::valid() const {
    return this->idx < this->map.hashTable.m;
}

TElem MapIterator::getCurrent() const {
    if(!this->valid()) throw std::exception();
    return this->map.hashTable.array[this->idx];
}