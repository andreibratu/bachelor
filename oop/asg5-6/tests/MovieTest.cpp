#include <assert.h>
#include "../ds/Vector.h"
#include "../model/Movie.h"


int main() {
  Movie m1{"Pulp Fiction", "Thriller", "coolaf.mp4", 1994};
  Movie key1{"", "Thriller", "", -1};
  Movie key2{"", "", "", -1};

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
