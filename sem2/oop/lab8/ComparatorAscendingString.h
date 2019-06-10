#ifndef COMP_ASC_STR_H
#define COMP_ASC_STR_H
#include <string>
#include "Comparator.h"

class ComparatorAscendingString: public Comparator<std::string> {
public:
  bool compare(const std::string& a, const std::string& b);
};
#endif
