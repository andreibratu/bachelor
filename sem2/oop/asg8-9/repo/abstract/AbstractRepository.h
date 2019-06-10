#ifndef ABSTRACT_REPO_H
#define ABSTRACT_REPO_H
#include <vector>
#include "../../exception/IndexException.h"

template <class T>
class AbstractRepository {
protected:
  AbstractRepository() = default;
public:
  std::vector<T> objects;

    std::vector<T> getAll() {
        return std::vector<T>(this->objects);
    }

    void remove(int idx) {
        if(0 > idx || idx >= (int)this->objects.size()) throw IndexException();

        this->objects.erase(this->objects.begin()+idx);
    }

    void add(const T& o) {
        this->objects.push_back(o);
    }

    T operator [] (int idx) const {
        return this->objects[idx];
    }

    ~AbstractRepository() = default;
};
#endif
