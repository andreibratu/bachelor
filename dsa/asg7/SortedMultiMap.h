//
// Created by andreib on 22.05.2019.
//

#ifndef ASG7_SORTEDMULTIMAP_H
#define ASG7_SORTEDMULTIMAP_H

#include <vector>
#include <utility>
#include <limits.h>
#include "SMMIterator.h"

#define NULL_VAL INT_MIN
#define EMPTY_ELEM (std::make_pair(NULL_VAL, NULL_VAL))
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

#define LEFT_CHILD(x) (2 * (x))
#define RIGHT_CHILD(x) (2 * (x) + 1)

using namespace std;

typedef bool(*Relation)(TKey, TKey);

class SMMIterator;

class SortedMultiMap {

friend class SMMIterator;

private:
    TElem* tree;
    int capacity;
    int count;
    Relation compare;
    // Resize the tree
    void resize();
    // Find first node with key equal with c
    int locateKey(TKey c) const;
    // Delete node
    void recursiveDelete(int idx);
public:
    // constructor
    SortedMultiMap(Relation r);

    //adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //removes a key value pair from the sorted multimap
    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};

#endif //ASG7_SORTEDMULTIMAP_H
