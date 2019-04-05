#ifndef USER_C_H
#define USER_C_H

#include "../repo/Repository.h"

class UserController {
private:
  Repository& r;
  std::vector<Movie> watchlist;
  std::vector<Movie> query;
  int current;
public:
  UserController(Repository& repo);

  void queryByGenre(const std::string&);

  void addToWatchList();

  void nextMovie();

  Movie seeDetails();

  void removeWatchlist(int, int);

  std::vector<Movie> getWatchlist();

  std::vector<Movie> getQuery();
};

#endif
