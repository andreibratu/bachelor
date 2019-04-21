#ifndef PERS_REPO_H
#define PERS_REPO_H
#include "AbstractRepository.h"

template <class T>
class PersistentRepository: virtual protected AbstractRepository<T> {
protected:
  virtual void load() = 0;

  virtual void save() = 0;
};
#endif
