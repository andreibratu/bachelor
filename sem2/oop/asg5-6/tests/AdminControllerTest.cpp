#include <assert.h>
#include "../controller/AdminController.h"


int main() {
  Repository r;
  AdminController c{r};

  r.addMovie(Movie{"asdf", "asdf", "asdf", 1998});
  assert(c.getAll().size() == 1);
  c.addMovie("super", "cool", "uber", 2019);
  assert(c.getAll().size() == 2);
  assert(c.getAll()[1].getTrailer() == "uber");
  c.updateName(0, "blanao");
  assert(c.getAll()[0].getName() == "blanao");
  c.updateGenre(1, "epic");
  assert(c.getAll()[1].getGenre() == "epic");
  c.addMovie("asdf", "asdf", "asdf", 2345);
  c.updateTrailer(2, "foobar");
  assert(c.getAll()[2].getTrailer() == "foobar");
  c.updateYear(2, 2019);
  assert(c.getAll()[2].getYear() == 2019);
  assert(c.deleteMovie(2));
  assert(!c.updateName(42, "qwerty"));
  assert(!c.deleteMovie(42));
  assert(!c.updateTrailer(42, "vaidemine"));

  return 0;
}
