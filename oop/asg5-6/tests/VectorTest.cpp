#include <assert.h>
#include "../ds/Vector.h"
#include "../model/Movie.h"

int main() {
  Vector<int> v;
  for(int i=0; i<100; i++) v.push_back(i);
  assert(v[42] == 42);
  assert(v.size() == 100);
  v.remove(42);
  assert(v[42] == 43);
  v.remove(78);
  v.remove(2);
  assert(v.size() == 97);

  Vector<Movie> cool;
  cool.push_back(Movie{"asdf", "asdf", "asdf", 1999});
  cool.push_back(Movie{"asdf", "asdf", "asdf", 1999});
  cool.push_back(Movie{"asdf", "asdf", "asdf", 1999});
  cool.remove(1);
  cool.remove(1);
  assert(cool.size() == 1);

  return 0;
}
