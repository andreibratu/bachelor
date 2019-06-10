//
// Created by andreib on 22.05.2019.
//

#ifndef ASG7_SMMITERATOR_H
#define ASG7_SMMITERATOR_H

#include "SortedMultiMap.h"
#include <vector>

class SortedMultiMap;

class SMMIterator {

friend class SortedMultiMap;

private:
    /*
     Constructor receives a reference of the container.
     after creation the iterator will refer to the first
     element of the container, or it will be invalid if
     the container is empty.
    */
    explicit SMMIterator(const SortedMultiMap& c);

    //contains a reference of the container it iterates over
    const SortedMultiMap& container;

    void traverse(int cIdx);

    int idx;

    std::vector<int> traversal;
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
    std::pair<int, int> getCurrent() const;
};

#endif //ASG7_SMMITERATOR_H
