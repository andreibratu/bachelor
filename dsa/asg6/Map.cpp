#include "Map.h"
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <cmath>

#define KNUTH_CT 0.6180339887
#define FRAC(x) ((x) - ((long)x))
#define EMPTY_ELEM (std::make_pair(-1, -1))

void Map::init(Map::NotAHashTableClass& t, int size) {
    t.size = size;
    t.hashF = [size](TElem e){return abs(e.first) % size;};
//    t.hashF = [&t](TKey e){return floor(t.size * FRAC(e * KNUTH_CT));};
    t.values = new TElem [t.size];
    t.next = new int [t.size];
    std::fill(t.values+0, t.values+t.size, EMPTY_ELEM);
    std::fill(t.next+0, t.next+t.size, NULL_TVALUE);
    t.firstFree = 0;
}

void Map::resize(Map::NotAHashTableClass& t) {
    NotAHashTableClass new_t{};
    init(new_t, t.size*2);

    // rehash
    for(int i = 0; i < t.size; i++) {
        if(t.values[i] == EMPTY_ELEM) continue;
        insert(new_t, t.values[i]);
    }

    uninit(t);

    t.size = new_t.size;
    t.hashF = new_t.hashF;
    t.firstFree = new_t.firstFree;
    t.values = new_t.values;
    t.next = new_t.next;
}

void Map::insert(Map::NotAHashTableClass &t, TElem k) {
    int i = t.hashF(k);

    if(t.values[i] == EMPTY_ELEM) {
        t.values[i] = k;
        t.next[i] = NULL_TVALUE;
    }
    else {
        if (t.firstFree == t.size) {
            resize(t);
        }
        int current = i;
        while(t.next[current] != NULL_TVALUE) {
            current = t.next[current];
        }
        t.values[t.firstFree] = k;
        t.next[t.firstFree] = NULL_TVALUE;
        t.next[current] = t.firstFree;
        changeFirstFree(t);
    }
}

TValue Map::remove(Map::NotAHashTableClass &t, TKey k) {
    int i = t.hashF({k, -1});
    int j = NULL_TVALUE;
    int idx = 0;

    assert(i >= 0);

    while(idx < t.size && j == NULL_TVALUE) {
        if(t.next[idx] == i) {
            j = idx;
        }
        else {
            idx++;
        }
    }

    while(i != NULL_TVALUE && t.values[i].first != k) {
        j = i;
        i = t.next[i];
    }

    if (i == NULL_TVALUE) return NULL_TVALUE;
    else {
        bool over = false;
        do {
            int p = t.next[i];
            int pp = i;
            while(p != NULL_TVALUE && t.hashF(t.values[p]) != i) {
                pp = p;
                p = t.next[p];
            }
            if(p == NULL_TVALUE) over = true;
            else {
                t.values[i] = t.values[p];
                j = pp;
                i = p;
            }
        } while(!over);
        if (j != NULL_TVALUE) {
            t.next[j] = t.next[i];
        }
        int old = t.values[i].second;
        t.values[i] = EMPTY_ELEM;
        t.next[i] = NULL_TVALUE;
        if(t.firstFree > i) {
            t.firstFree = i;
        }

        return old;
    }
}

TValue Map::search(const Map::NotAHashTableClass &t, TKey k) const {
    int i = t.hashF({k, -1});

    while(i != NULL_TVALUE && t.values[i].first != k) {
        i = t.next[i];
    }

    if(i == NULL_TVALUE) return NULL_TVALUE;

    return t.values[i].first;
}

void Map::uninit(Map::NotAHashTableClass &t) {
    delete[] t.values;
    delete[] t.next;
}

Map::Map() {
    count = 0;
    init(table, 20);
}

TValue Map::add(TKey c, TValue v) {
    TValue old = remove(table, c);
    insert(table, {c, v});

    // Count actually increased
    if(old == NULL_TVALUE) count += 1;

    return old;
}

TValue Map::search(TKey c) const {
    int idx = search(table, c);
    if(idx == NULL_TVALUE) return NULL_TVALUE;
    else return table.values[idx].second;
}

TValue Map::remove(TKey c) {
    TValue result = remove(table, c);
    if(result != NULL_TVALUE) count-=1;

    return result;
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

void Map::changeFirstFree(Map::NotAHashTableClass &t) {
    t.firstFree++;
    while(t.firstFree < t.size && t.values[t.firstFree] != EMPTY_ELEM) {
        t.firstFree++;
    }
}
