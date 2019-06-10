#ifndef MOVIE_REPO_H
#define MOVIE_REPO_H

#include "../abstract/AbstractRepository.h"
#include "../../model/Movie.h"

class MovieRepository: virtual public AbstractRepository<Movie> {
public:
  void updateName(int idx, const std::string& name);

  void updateGenre(int idx, const std::string& genre);

  void updateTrailer(int idx, const std::string& trailer);

  void updateYear(int idx, int year);

  void incrementLikes(int idx);
};
#endif
