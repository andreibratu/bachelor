#include "assert.h"
#include "../repo/movie/MovieRepository.h"
#include "base/UserController.h"


int main() {
  MovieRepository r;
  MovieRepository w;
  UserController c{r, w};

  // Remove Movies objects init by .csv
  while(c.getWatchlist().size()) {
    c.removeWatchlist(0, 0);
  }

  c.queryByGenre("drama");
  std::cout << c.getQuery().size() << '\n';
  assert(c.getQuery().size() == 3);
  for(int i = 0; i < 3; i++) {
    c.nextMovie();
  }

  Movie m = c.seeDetails();
  assert(m.getName() == "The Shawshank Redemption");

  c.addToWatchList();
  assert(c.getWatchlist()[0].getName() == "The Shawshank Redemption");

  c.queryByGenre("drama");
  assert(c.getQuery().size() == 2);

  c.removeWatchlist(0, 1);
  c.queryByGenre("drama");
  assert(c.getQuery()[0].getLikes() == 1);

  return 0;
}
