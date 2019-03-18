#include "../repo/MedicationRepository.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  char n1[] = "asdf";
  char n2[] = "cvbn";
  char n3[] = "asdf";

  Medication* m1 = medication_init(n1, 3.5, 6, 4);
  Medication* m2 = medication_init(n3, 3.5, 3, 4);
  Medication* m3 = medication_init(n2, 4, 2, 6);

  MedicationRepository* mr = repository_init();
  
  assert(mr->medication->size == 1);
  repository_addMedication(mr, m2);
  assert(mr->medication->size == 1);
  assert(mr->medication->medications[0]->quantity == 9);
  repository_addMedication(mr, m3);
  repository_addMedication(mr, m1);
  assert(mr->medication->size == 2);
  repository_deleteMedication(mr, n2, 4);
  assert(mr->medication->size == 1);
  repository_updateMedicationQuantity(mr, n1, 3.5, 2);
  assert(mr->medication->medications[0]->quantity == 11);
  repository_updateMedicationPrice(mr, n1, 3.5, 4);
  assert(mr->medication->medications[0]->price == 8);
  MedicationVector* mv = repository_getAll(mr);
  int i;
  for(i=0; i<mv->size; i++) {
    Medication* m = mv->medications[i];
    assert(m->name != 0);
  }
  repository_destructor(mr);
  // free(m1);
  // free(m2);
  // free(m3);
  return 0;
}
