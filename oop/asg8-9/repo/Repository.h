#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>
#include <vector>
#include "../model/Movie.h"

class Repository {
  friend class UserController;
private:
  std::vector<Movie> movies;
public:
  Repository();

  std::vector<Movie> getAll();

  void addMovie(const Movie& m);

  void deleteMovie(int idx);

  void updateName(int idx, const std::string& name);

  void updateGenre(int idx, const std::string& genre);

  void updateTrailer(int idx, const std::string& trailer);

  void updateYear(int idx, int year);

  void incrementLikes(int idx);

  Movie operator [] (int idx) const;
};

#endif
