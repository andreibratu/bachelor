#include <assert.h>
#include "../model/Movie.h"


int main() {
  Movie m1{"Pulp Fiction", "Thriller", "coolaf.mp4", 1994};
  Movie key1{"", "Thriller", "", -1};
  Movie key2{"", "", "", -1};

  Movie m2 = m1;
  m2 = Movie(m1);
  assert(m1 == m2);
  assert(m1 == key1);

  std::cout << m2;

  m2.setName("supercool");
  m2.setGenre("Wow");
  m2.setYear(2015);
  m2.setTrailer("why");

  assert(m2.getName() != m1.getName());
  assert(m2.getYear() == 2015);
  assert(m2.getTrailer() == "why");
  assert(m2.getGenre() == "Wow");

  m1.setLikes(42);
  assert(m1.getLikes() == 42);
  assert(m1 == key1);
  assert(m1 == key2);
  ++m1;
  ++m1;
  assert(m1.getLikes() == 44);
  m1++;
  assert(m1.getLikes() == 45);

  return 0;
}
