#include <assert.h>
#include "../repo/Repository.h"
#include "../model/Movie.h"

int main() {
  Repository r;
  r.addMovie(Movie{"asdf", "comedy", "asdf", 2007});
  r.addMovie(Movie{"asdf2", "comedy", "erty", 2009});
  Vector<Movie> all = r.getAll();
  assert(all.size() == 2);

  all.remove(0);

  all[0].setName("megacool");
  assert(r[0].getName() != "megacool");
  r.incrementLikes(0);
  assert(r[0].getLikes() == 1);
  assert(r.getAll()[0].getLikes() == 1);
  r.deleteMovie(0);
  assert(r.getAll().size() == 1);

  assert(!r.deleteMovie(42));

  assert(r.updateName(0, "supercool"));
  assert(!r.updateName(42, "boi"));

  assert(r.updateGenre(0, "sad"));
  assert(!r.updateGenre(42, "boi"));


  assert(r.updateTrailer(0, "wow.mp4"));
  assert(!r.updateTrailer(42, "boi"));

  assert(r.updateYear(0, 1345));
  assert(!r.updateYear(1344, 1212));

  assert(r.incrementLikes(0));
  assert(!r.incrementLikes(42));


  std::cout << all << '\n';
  // 
  // for(int i = 0; i < 10; i++) {
  //   all.push_back(Movie{"asdf", "comedy", "asdf", 2007});
  // }
  // all = r.getAll();
  // Vector<Movie> other = Vector<Movie>(all);
  return 0;
}
