#include "../ds/MedicationVector.h"
#include "../model/Medication.h"
#include <assert.h>
#include <string.h>

int main() {
  char n1[] = "asdf";
  char n2[] = "erty";
  char n3[] = "uiop";

  Medication* m1 = medication_init(n1, 5.7, 3, 6);
  Medication* m2 = medication_init(n2, 4.5, 2, 8);
  Medication* m3 = medication_init(n3, 5.6, 4, 7);

  MedicationVector* mv = vector_init(2);
  vector_add(mv, m1);
  assert(mv->size == 1);
  vector_add(mv, m2);
  assert(mv->size == 2);
  assert(mv->capacity == 2);
  vector_add(mv, m3);
  assert(mv->size == 3);
  assert(mv->capacity == 4);
  vector_remove(mv, n1, 5.7);
  assert(mv->size == 2);
  assert(strcmp(mv->medications[0]->name, n2) == 0);
  vector_destructor(mv);

  return 0;
}
