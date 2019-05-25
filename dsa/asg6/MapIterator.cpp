//
// Created by andreib on 15.05.2019.
//

#include <exception>
#include "MapIterator.h"
#define EMPTY_ELEM (std::make_pair(INT_MIN, INT_MIN))

MapIterator::MapIterator(const Map& m): container{m} {
    idx=0;
    first();
}

void MapIterator::first() {
    idx = 0;
    while(idx < container.capacity && container.values[idx] == EMPTY_ELEM)
    {
        idx++;
    }
}

void MapIterator::next() {
    if(!this->valid()) throw std::exception();
    idx++;
    while(idx < container.capacity && container.values[idx] == EMPTY_ELEM)
    {
        idx++;
    }
}

bool MapIterator::valid() const {
    return container.count > 0 && idx < container.capacity;
}

TElem MapIterator::getCurrent() const {
    if(!this->valid()) throw std::exception();
    return container.values[idx];
}