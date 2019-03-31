#include "assert.h"
#include "../repo/Repository.h"
#include "../controller/UserController.h"


int main() {
  Repository r;
  r.addMovie(Movie{"The Shawshank Redemption", "Drama", "https://youtu.be/6hB3S9bIaco", 1994});
  r.addMovie(Movie{"Casablanca", "Drama", "https://youtu.be/BkL9l7qovsE", 1942});
  r.addMovie(Movie{"One Flew Over the Cuckoo's Nest", "Drama", "https://youtu.be/OXrcDonY-B8", 1975});
  UserController c{r};

  Vector<Movie> q = c.queryByGenre("drama");
  assert(q.size() == 3);
  for(int i = 0; i < 4; i++) {
    c.nextMovie();
  }

  c.addToWatchList();
  assert(c.getWatchlist()[0].getName() == "The Shawshank Redemption");
  c.removeWatchlist(0, 1);
  assert(c.queryByGenre("drama")[0].getLikes() == 1);

  return 0;
}
