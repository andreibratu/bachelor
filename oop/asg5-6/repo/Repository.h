#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <string>
#include "../ds/Vector.h"
#include "../model/Movie.h"

class Repository {
private:
  Vector<Movie>& movies;
public:
  Repository(Vector<Movie>& movies);

  Vector<Movie> getAll() const;

  void addMovie(Movie m);

  bool deleteMovie(int idx);

  bool updateName(int idx, std::string name);

  bool updateGenre(int idx, std::string genre);

  bool updateTrailer(int idx, std::string trailer);

  bool updateYear(int idx, int year);

  bool incrementLikes(int idx);

  Movie& operator [] (int idx) const;
};

#endif
