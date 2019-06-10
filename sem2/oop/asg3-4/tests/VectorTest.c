#include <assert.h>
#include "../ds/Vector.h"
#include "../model/Medication.h"
#include "stdlib.h"


int main() {
  char n1[] = "aspirina";
  char n2[] = "aspirina";
  char n4[] = "parasinus";

  Medication* m1 = medication_init(n1, 4.5, 5, 8);
  Medication* m2 = medication_init(n2, 5, 7, 10);
  Medication* m4 = medication_init(n4, 6, 5, 12);
  void (*destructor)(TElem) = (void (*) (TElem)) medication_destructor;

  Vector* v = vector_init();
  vector_add(v, m1);
  assert(v->size == 1);
  assert(v->capacity == 1);
  vector_add(v, m2);
  assert(v->capacity == 2);
  vector_add(v, m4);
  assert(v->size == 3);
  vector_remove(v, 2, destructor);
  assert(v->size == 2);
  vector_destructor(v, destructor);

  return 0;
}
