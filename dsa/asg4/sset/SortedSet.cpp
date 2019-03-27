#include "SortedSet.h"


SortedSet::SortedSet(Relation r) {
  this->r = r;
}


bool SortedSet::add(TComp e) {
  if(this->search(e)) return false;

  SortedSetIterator it = this->items.getIterator();
  for(; it.valid(); it.next()) {
    Relation comp = *this->r;
    if(comp(e, it.getCurrent())) {
      this->items.addBefore(it.getIdx(), e);
      return true;
    }
  }

  this->items.insert(e);
  return true;
}


bool SortedSet::remove(TComp e) {
  SortedSetIterator it = this->items.getIterator();
  for(; it.valid(); it.next()) {
    if(it.getCurrent() == e) {
      this->items.remove(it.getIdx());
      return true;
    }
  }

  return false;
}


bool SortedSet::search(TComp e) const {
  SortedSetIterator it = this->items.getIterator();
  for(; it.valid(); it.next()) {
    if(it.getCurrent() == e) {
      return true;
    }
  }

  return false;
}


int SortedSet::size() const {
  return this->items.getSize();
}


bool SortedSet::isEmpty() const {
  return this->items.getSize() == 0;
}


SortedSetIterator SortedSet::iterator() const {
  return this->items.getIterator();
}


SortedSet::~SortedSet() {}
