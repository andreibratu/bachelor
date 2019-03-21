#ifndef ITER_H
#define ITER_H

#include <vector>

class Vertex;

template <class T>
class Iterator {
private:
  const std::vector<T>& c;
  typename std::vector<T>::const_iterator it;
public:
  /**
    Iterator constructor.

    @param `c` The vector to iterate over.
  */
  Iterator(const std::vector<T>& c);

  // Return iterator to first element.
  void first();

  // @return: The iterator did not reach the end of the container
  bool valid() const;

  // @return: Current iterated element
  T getCurrent() const;

  // Move iterator
  void next();
};

template class Iterator<int>;
template class Iterator<Vertex>;

#endif
