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
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

using namespace std;

typedef bool(*Relation)(TKey, TKey);

class SMMIterator;

class SortedMultiMap {

friend class SMMIterator;

private:
    struct Node
    {
        TElem value;
        int leftChild;
        int rightChild;
        int parent;

        bool operator == (const Node& other) const
        {
            return value == other.value &&
                   leftChild == other.leftChild &&
                   rightChild == other.rightChild;
        }

        bool operator != (const Node& other) const
        {
            return !(*this==other);
        }
    };

    struct Stack
    {
        int* values;
        int size;
        int current;

        Stack()
        {
            size = 42;
            values = new int [size];
            current = -1;
        }

        Stack(int s)
        {
            size = s;
            values = new int [size];
            current = -1;
        }

        void push(int x) {values[++current] = x;}

        int pop() {return values[current--];}

        bool empty() {return current == -1;}

        void resize(int newSize)
        {
            delete[] values;
            values = new int [newSize];
            size = newSize;
            current = -1;
        }

        Stack(const Stack& other)
        {
            delete[] values;
            size = other.size;
            current = other.current;
            values = new int [size];
            for(int i = 0; i < size; i++) values[i] = other.values[i];
        }


        Stack& operator = (const Stack& other)
        {
            delete[] values;
            size = other.size;
            current = other.current;
            values = new int [size];
            for(int i = 0; i < size; i++) values[i] = other.values[i];
        }

        ~Stack() {delete[] values;}
    };

    Node* tree;
    Stack freeSpace;
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
    Node EMPTY_ELEM = Node{{NULL_VAL, NULL_VAL}, NULL_VAL, NULL_VAL, NULL_VAL};

    // Remove all values associated to given key
    std::vector<TValue> removeKey(TKey key);

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
