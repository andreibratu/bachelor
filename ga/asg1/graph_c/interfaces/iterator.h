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
  Iterator(const std::vector<T>& c);

  void first();

  bool valid() const;

  T getCurrent() const;

  void next();
};

template class Iterator<int>;
template class Iterator<Vertex>;

#endif
