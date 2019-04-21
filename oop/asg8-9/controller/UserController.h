#ifndef USER_C_H
#define USER_C_H

#include "../repo/movie/MovieRepository.h"

class UserController {
private:
  int current;
  MovieRepository& watchlist;
  MovieRepository& repository;
  std::vector<Movie> query;
public:
  UserController(MovieRepository& repo, MovieRepository& watchlist);

  void queryByGenre(const std::string&);

  void addToWatchList();

  void nextMovie();

  Movie seeDetails();

  void removeWatchlist(int, int);

  std::vector<Movie> getWatchlist();

  std::vector<Movie> getQuery();
};

#endif
