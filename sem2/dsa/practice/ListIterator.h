//
// Created by andreib on 26.06.2019.
//

#ifndef PRACTICE_LISTITERATOR_H
#define PRACTICE_LISTITERATOR_H

#include "IndexedList.h"

class ListIterator
{

friend class IndexedList;

private:
    const IndexedList& container;
    int it;
    //Constructor receives a reference of the container.
    //after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty
    explicit ListIterator(const IndexedList& c);
public:
    //sets the iterator to the first element of the container
    void first();

    //moves the iterator to the next element
    //throws exception if the iterator is not valid
    void next();

    //checks if the iterator is valid
    bool valid() const;

    //returns the value of the current element from the iterator
    // throws exception if the iterator is not valid
    TElem getCurrent() const;
};


#endif //PRACTICE_LISTITERATOR_H
