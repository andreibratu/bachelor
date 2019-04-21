#ifndef ADMIN_CONTROLLER_H
#define ADMIN_CONTROLLER_H

#include "../repo/movie/MovieRepository.h"
#include "../model/Movie.h"

class AdminController{
private:
  MovieRepository& repository;
public:
  explicit AdminController(MovieRepository& r);

  std::vector<Movie> getAll();

  void addMovie(const std::string& n, const std::string& g, const std::string& t, int y);

  void deleteMovie(int idx);

  void updateName(int idx, const std::string& name);

  void updateGenre(int idx, const std::string& genre);

  void updateTrailer(int idx, const std::string& trailer);

  void updateYear(int idx, int year);
};
#endif
