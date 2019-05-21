//
// Created by andreib on 15.05.2019.
//

#include <exception>
#include "MapIterator.h"
#define EMPTY_ELEM (std::make_pair(-1, -1))

MapIterator::MapIterator(const Map& m): container{m} {
    idx=0;
    first();
}


void MapIterator::first() {
    idx = 0;
    while(idx < container.table.size && container.table.values[idx] == EMPTY_ELEM) {
        idx++;
    }
}

void MapIterator::next() {
    if(!valid()) throw std::exception();
    idx++;
    while(idx < container.table.size && container.table.values[idx] == EMPTY_ELEM) {
        idx++;
    }
}

bool MapIterator::valid() const {
    return idx != container.table.size;
}

TElem MapIterator::getCurrent() const {
    if(!valid()) throw std::exception();
    return container.table.values[idx];
}