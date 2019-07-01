//
// Created by andreib on 26.06.2019.
//

#ifndef PRACTICE_INDEXEDLIST_H
#define PRACTICE_INDEXEDLIST_H

#include <limits.h>

#define NIL INT_MIN
typedef int TElem;

class ListIterator;

class IndexedList {

friend class ListIterator;

private:
    TElem *elements;
    TElem *next;
    int capacity;
    int count;
    int head;
    int freePos;
    void updateFreePos();
    void resize();
public:
    IndexedList(const IndexedList &other);

    IndexedList& operator = (const IndexedList &other);

    // constructor
    IndexedList();

    // returns the number of elements from the list
    int size() const;

    // verifies if the list is empty
    bool isEmpty() const;

    TElem getElement(int pos) const;

    // modifes an element from a given position
    //returns the old value from the position
    //throws an exception if the position is not valid
    TElem setElement(int pos, TElem e);

    // adds an element to the end of the list
    void addToEnd(TElem e);

    // adds an element to a given position
    //throws an exception if the position is not valid
    void addToPosition(int pos, TElem e);

    // removes an element from a given position
    //returns the removed element
    //throws an exception if the position is not valid
    TElem remove(int pos);

    // searches for an element and returns the first position
    // where the element appears or -1 if the element is not in the list
    int search(TElem e) const;

    // returns an iterator set to the first element of the list
    // or invalid if the list is empty
    ListIterator iterator() const;

    //destructor
    ~IndexedList();
};

#endif //PRACTICE_INDEXEDLIST_H
