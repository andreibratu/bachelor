#include <assert.h>
#include "../repo/movie/MovieRepository.h"
#include "../model/Movie.h"

int main() {
  MovieRepository r;
  r.add(Movie{"asdf", "comedy", "asdf", 2007});
  r.add(Movie{"asdf2", "comedy", "erty", 2009});
  std::vector<Movie> all = r.getAll();
  assert(all.size() == 2);

  all.erase(all.begin());

  all[0].setName("megacool");
  assert(r[0].getName() != "megacool");
  r.incrementLikes(0);
  assert(r[0].getLikes() == 1);
  assert(r.getAll()[0].getLikes() == 1);
  r.remove(0);
  assert(r.getAll().size() == 1);

  try {r.remove(42);} catch (std::exception e) {}
  try {r.updateName(42, "boi");} catch (std::exception e) {}
  try {r.updateGenre(42, "boi");} catch (std::exception e) {}
  try {r.updateTrailer(42, "boi");} catch (std::exception e) {}
  try {r.updateYear(1344, 1212);} catch (std::exception e) {}
  try {r.incrementLikes(42);} catch (std::exception e) {}


  r.updateGenre(0, "sad");
  r.updateTrailer(0, "wow.mp4");
  r.updateYear(0, 1345);
  r.incrementLikes(0);

  return 0;
}
