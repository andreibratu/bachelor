#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <string>
#include "../ds/Vector.h"
#include "../model/Movie.h"

class Repository {
  friend class UserController;
private:
  Vector<Movie> movies;
public:
  Repository();

  Vector<Movie> getAll();

  void addMovie(const Movie& m);

  bool deleteMovie(int idx);

  bool updateName(int idx, const std::string& name);

  bool updateGenre(int idx, const std::string& genre);

  bool updateTrailer(int idx, const std::string& trailer);

  bool updateYear(int idx, int year);

  bool incrementLikes(int idx);

  Movie& operator [] (int idx) const;
};

#endif
