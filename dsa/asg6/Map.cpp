//
// Created by andreib on 27.04.2019.
//

#include "Map.h"
#include "MapIterator.h"

Map::Map() {
    this->count = 0;
    this->empty_elem = std::make_pair(-1, -1);

    auto hash_f = [](TElem e){ return e.first % 47; };
    auto equal_f = [](TElem e1, TElem e2){ return e1.first == e2.first; };

    int (*hash)(TElem) = hash_f;
    bool (*equal)(TElem, TElem) = equal_f;

    this->hashTable = HashTable<TElem>{hash, equal, this->empty_elem};
}

TValue Map::add(TKey c, TValue v) {
    int oldVal = this->search(c);
    if(oldVal != NULL_TVALUE) {
        this->hashTable.remove({c, v});
        this->count--;
    }

    this->hashTable.add({c, v});
    this->count++;
    return oldVal;
}

TValue Map::search(TKey c) const {
    TElem e = this->hashTable.find({c, NULL_TVALUE});

    if(e.first == this->empty_elem.first) return NULL_TVALUE;
    else return e.second;
}

TValue Map::remove(TKey c) {
    TElem e = this->hashTable.find({c, NULL_TVALUE});

    if(e.first == this->empty_elem.first) return NULL_TVALUE;
    else {
        this->hashTable.remove({c, NULL_TVALUE});
        this->count--;
        return e.second;
    }
}

int Map::size() const {
    return this->count;
}

bool Map::isEmpty() const {
    return this->count == 0;
}

MapIterator Map::iterator() const {
    return MapIterator(*this);
}

Map::~Map() = default;
