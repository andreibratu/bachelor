#ifndef PARSE_EXC_H
#define PARSE_EXC_H
#include <stdexcept>

class ParseException: public std::runtime_error {
public:
  explicit ParseException(): runtime_error("Could not parse the given number!") {}
};
#endif
