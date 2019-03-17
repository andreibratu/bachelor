#ifndef VERTEX_IT_H
#define VERTEX_IT_H

#include <vector>


template <class T>
class VertexIterator {
private:
  const std::vector<T>& c;
  typename std::vector<T>::const_iterator it;
public:
  VertexIterator(const std::vector<T>& c);

  void first();

  bool valid() const;

  T getCurrent() const;

  void next();
};

#endif
