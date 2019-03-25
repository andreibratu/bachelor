#include <assert.h>
#include "../repo/Repository.h"
#include "../model/Movie.h"

int main() {
  Vector<Movie> v;
  v.push_back(Movie{"asdf", "comedy", "asdf", 2007});
  v.push_back(Movie{"asdf2", "comedy", "erty", 2009});
  Repository r{v};
  Vector<Movie> all = r.getAll();
  assert(all.size() == 2);
  all[0].setName("megacool");
  Vector<Movie> all2 = r.getAll();
  assert(all2[0].getName() != "megacool");
  r.incrementLikes(0);
  assert(r[0].getLikes() == 1);
}
