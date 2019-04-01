#ifndef USER_C_H
#define USER_C_H

#include "../ds/Vector.h"
#include "../repo/Repository.h"

class UserController {
private:
  Repository& r;
  Vector<Movie> watchlist;
  Vector<Movie> query;
  int current;
public:
  UserController(Repository& repo);

  void queryByGenre(const std::string&);

  void addToWatchList();

  void nextMovie();

  Movie seeDetails();

  void removeWatchlist(int, int);

  Vector<Movie> getWatchlist();

  Vector<Movie> getQuery();
};

#endif
