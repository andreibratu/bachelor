#ifndef IDX_EXC_H
#define IDX_EXC_H
#include <stdexcept>

class IndexException: public std::runtime_error {
public:
  explicit IndexException(): runtime_error("Invalid index!") {}
};
#endif
