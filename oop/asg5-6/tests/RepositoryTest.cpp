#include <assert.h>
#include "../repo/Repository.h"
#include "../model/Movie.h"

int main() {
  Repository r;
  r.addMovie(Movie{"asdf", "comedy", "asdf", 2007});
  r.addMovie(Movie{"asdf2", "comedy", "erty", 2009});
  Vector<Movie> all = r.getAll();
  assert(all.size() == 2);
  all[0].setName("megacool");
  r.incrementLikes(0);
  assert(r[0].getLikes() == 1);
  assert(r.getAll()[0].getLikes() == 1);
}
