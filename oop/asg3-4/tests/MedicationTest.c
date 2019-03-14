#include "../model/Medication.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main() {
  char n1[] = "aspirina";
  char n2[] = "aspirina";
  char n3[] = "aspirina";
  char n4[] = "parasinus";

  Medication* m1 = medication_init(n1, 4.5, 5, 8);
  Medication* m2 = medication_init(n2, 5, 7, 10);
  Medication* m3 = medication_init(n3, 4.5, 2, 8);
  Medication* m4 = medication_init(n4, 6, 5, 12);

  assert(sort_ascending(m1, m2) == -1);
  assert(sort_ascending(m1, m3) == 0);
  assert(sort_ascending(m4, m1) == 1);

  assert(sort_descending(m3, m4) == 1);
  assert(sort_descending(m1, m2) == 1);
  assert(sort_descending(m1, m3) == 0);
  
  assert(same(m1, n3, 4.5) == 1);

  medication_destructor(m1);
  medication_destructor(m2);
  medication_destructor(m3);
  medication_destructor(m4);

  return 0;
}
