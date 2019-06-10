#ifndef COMP_DESC_INT_H
#define COMP_DESC_INT_H
#include "Comparator.h"

class ComparatorDescendingInteger: public Comparator<int> {
public:
  bool compare(const int& a, const int& b);
};
#endif
