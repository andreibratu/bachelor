#pragma once

#include <vector>


class VertexIterator {
private:
  const std::vector<int>& c;
  std::vector<int>::const_iterator it;
public:
  VertexIterator(const std::vector<int>& c);

  void first();

  bool valid() const;

  int getCurrent() const;

  void next();
};
