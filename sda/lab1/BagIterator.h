#pragma once
#include "Bag.h"

typedef int TElem;

class Bag;

class BagIterator {

  friend class Bag;

private:
  BagIterator(const Bag& c);
  const Bag& c;
  int idx;
  int how_many;
  int current;

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
