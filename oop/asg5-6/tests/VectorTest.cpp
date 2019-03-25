#include <assert.h>
#include "../ds/Vector.h"

int main() {
  Vector<int> v;
  for(int i=0; i<100; i++) v.push_back(i);
  assert(v.size() == 100);
  v.remove(42);
  assert(v.find(42) == -1);
  assert(v.find(99) == 98);
  return 0;
}
