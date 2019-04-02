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
      this->items.addBefore(it.getCurrent(), e);
      return true;
    }
  }

  this->items.addEnd(e);
  return true;
}


bool SortedSet::remove(TComp e) {
  if(!this->items.search(e)) return false;

  this->items.remove(e);
  return true;
}


bool SortedSet::search(TComp e) const {
  return this->items.search(e);
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
