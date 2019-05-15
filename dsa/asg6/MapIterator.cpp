//
// Created by andreib on 15.05.2019.
//

#include <exception>
#include "MapIterator.h"


MapIterator::MapIterator(const Map& m): container{m} {
    idx=0;
    first();
}


void MapIterator::first() {
    idx = 0;
    while(container.table.values[idx] == container.table.EMPTY_ELEM) {
        idx++;
    }
}

void MapIterator::next() {
    if(!valid()) throw std::exception();
    idx++;
    while(container.table.values[idx] == container.table.EMPTY_ELEM && idx < container.table.size) {
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