#ifndef LIKE_EXC_H
#define LIKE_EXC_H
#include <stdexcept>

class LikeException: public std::runtime_error {
public:
  explicit LikeException(): runtime_error("Invalid like option!") {}
};
#endif
