#include <assert.h>
#include "../controller/AdminController.h"


int main() {
  MovieRepository r;
  AdminController c{r};

  // Remove Movies read from .csv for a blank slate
  while(c.getAll().size()) {
    c.deleteMovie(0);
  }

  r.add(Movie{"asdf", "asdf", "asdf", 1998});
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
  c.deleteMovie(2);
  try {c.updateName(42, "qwerty");} catch(std::exception e) {}
  try {c.deleteMovie(42);} catch(std::exception e) {}
  try {c.updateTrailer(42, "vaidemine");} catch(std::exception e) {}

  return 0;
}
