#ifndef COMP_H
#define COMP_H
template <class T>
class Comparator {
public:
  virtual bool compare(const T& a, const T& b) = 0;
};
#endif
