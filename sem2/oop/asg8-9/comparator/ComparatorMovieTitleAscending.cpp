#include "ComparatorMovieTitleAscending.h"

bool ComparatorMovieTitleAscending::compare(const Movie& a, const Movie& b) {
  return a.getName() > b.getName();
}
