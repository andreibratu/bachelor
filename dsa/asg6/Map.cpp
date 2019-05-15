#include "Map.h"
#include <algorithm>

void Map::init(Map::NotAHashTableClass& t, int size) {
    t.size = size;
    t.values = new TElem [t.size];
    t.EMPTY_ELEM = {-1, -1};
    t.next = new int [t.size];
    t.freePos = size-1;
    t.hashF = [&t](TElem e){return e.first % (t.size/2);};

    std::fill(t.values+0, t.values+t.size, t.EMPTY_ELEM);
    std::fill(t.next+0, t.next+t.size, NULL_TVALUE);
}


void Map::resize(Map::NotAHashTableClass& t) {
    NotAHashTableClass new_t{};
    init(new_t, t.size*2);

    // rehash
    for(int i = 0; i < t.size / 2; i++) {
        int pos = i;
        if(t.values[pos] == t.EMPTY_ELEM) continue;

        do {
            add(new_t, t.values[pos]);
            if(t.next[pos] != NULL_TVALUE) pos = t.next[pos];
        } while(t.next[pos] != NULL_TVALUE);
    }

    uninit(t);

    t.size = new_t.size;
    t.hashF = new_t.hashF;
    t.freePos = new_t.freePos;
    t.values = new_t.values;
    t.next = new_t.next;
}

void Map::add(Map::NotAHashTableClass &t, TElem e) {
    int pos = t.hashF(e);

    if(t.values[pos] == t.EMPTY_ELEM) {
        t.values[pos] = e;
        return;
    }

    while(t.next[pos] != NULL_TVALUE) {
        pos = t.next[pos];
    }

    if(t.freePos == t.size / 2 -1) resize(t);

    t.values[t.freePos] = e;
    t.next[t.freePos] = NULL_TVALUE;
    t.next[pos] = t.freePos;

    t.freePos -= 1;
}

TElem Map::remove(Map::NotAHashTableClass &t, TElem e) {
    int pos = t.hashF(e);

    // Happens to be the first element
    if(t.values[pos].first == e.first) {
        TElem val = t.values[pos];
        t.values[pos] = t.EMPTY_ELEM;

        return val;
    }

    // No other element with the same hash
    if(t.next[pos] == NULL_TVALUE) return t.EMPTY_ELEM;

    int nextPos = t.next[pos];
    while(t.values[nextPos].first != e.first && t.next[nextPos] != NULL_TVALUE) {
        pos = nextPos;
        nextPos = t.next[nextPos];
    }

    // Found it
    if(t.values[nextPos].first == e.first) {
        t.next[pos] = t.next[nextPos];
        TElem old = t.values[nextPos];
        t.values[nextPos] = t.EMPTY_ELEM;

        return old;
    }

    return  t.EMPTY_ELEM;
}

TElem Map::find(const Map::NotAHashTableClass &t, TElem e) const {
    int pos = t.hashF(e);

    while(t.values[pos].first != e.first && t.next[pos] != NULL_TVALUE) {
        pos = t.next[pos];
    }

    if(t.values[pos].first == e.first) {
        return t.values[pos];
    }

    return t.EMPTY_ELEM;
}

void Map::uninit(Map::NotAHashTableClass &t) {
    delete[] t.values;
    delete[] t.next;
}

Map::Map() {
    count = 0;
    init(table, 100);
}

TValue Map::add(TKey c, TValue v) {
    TElem old = remove(table, {c, NULL_TVALUE});
    add(table, {c, v});

    // Count actually increased
    if(old == table.EMPTY_ELEM) count += 1;

    return old.second;
}

TValue Map::search(TKey c) const {
    return find(table, {c, NULL_TVALUE}).second;
}

TValue Map::remove(TKey c) {
    TElem result = remove(table, {c, NULL_TVALUE});
    if(result != table.EMPTY_ELEM) count-=1;

    return result.second;
}

int Map::size() const {
    return count;
}

bool Map::isEmpty() const {
    return count == 0;
}


MapIterator Map::iterator() const {
    return MapIterator(*this);
}

Map::~Map() {
    uninit(table);
}