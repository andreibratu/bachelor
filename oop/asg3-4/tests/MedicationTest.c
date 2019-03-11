#include "model/Medication.h"
#include <assert.h>
#include <string.h>

int main() {
  char n1[] = "aspirina";
  char n2[] = "aspirina";
  char n3[] = "aspirina";
  char n4[] = "parasinus";

  Medication* m1 = init(n1, 4.5, 5, 8);
  Medication* m2 = init(n2, 5, 7, 10);
  Medication* m3 = init(n3, 4.5, 2, 8);
  Medication* m4 = init(n4, 6, 5, 12);

  assert(cmp(m1, m2) != 0);
  assert(cmp(m1, m3) == 0);
  assert(cmp(m1, m4) != 0);
  assert(same(m1, n3, 4.5) == 1);

  destroy(m1);
  destroy(m2);
  destroy(m3);
  destroy(m4);
}
