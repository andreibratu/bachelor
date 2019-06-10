#ifndef COMP_MOVIE_ASC_H
#define COMP_MOVIE_ASC_H

#include "Comparator.h"
#include "../model/Movie.h"

class ComparatorMovieTitleAscending: public Comparator<Movie> {
public:
  bool compare(const Movie& a, const Movie& b);
};
#endif
