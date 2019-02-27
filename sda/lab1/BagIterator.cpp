#include "BagIterator.h"
#include "Bag.h"

BagIterator::BagIterator(const Bag& c) {
    this->c = c;
    this->idx = 0;
    this->how_many = 0;
    this->current = 0;
}

void BagIterator::first() {
    this->idx = 0;
    this->how_many = this->c.array[idx].apparitions;
    this->current = this->c.array[idx].element;
}

void BagIterator::next() {
    if (this->how_many > 0) {
        how_many -= 1;
    }
    else {
        this->idx += 1;
        if (this->valid()) {
            this->how_many = this->c.array[idx].apparitions;
            this->current = this->c.array[idx].element;
        }
    }
}

bool BagIterator::valid() const {
    return this->idx < c.size();
}

TElem BagIterator::getCurrent() const {
    return this->current;
}
