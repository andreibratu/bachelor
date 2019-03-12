#include "../repo/MedicationRepository.h"
#include <assert.h>

int main() {
  char n1[] = "asdf";
  char n2[] = "cvbn";
  char n3[] = "asdf";

  MedicationRepository* mr = repository_init();

  addMedication(mr, n1, 3.5, 6, 4);
  assert(mr->medication->size == 1);
  addMedication(mr, n3, 3.5, 3, 4);
  assert(mr->medication->size == 1);
  assert(mr->medication->medications[0]->quantity == 9);
  addMedication(mr, n2, 4, 2, 6);
  assert(mr->medication->size == 2);
  deleteMedication(mr, n2, 4);
  assert(mr->medication->size == 1);
  updateMedicationQuantity(mr, n1, 3.5, 2);
  assert(mr->medication->medications[0]->quantity == 11);
  updateMedicationPrice(mr, n1, 3.5, 4);
  assert(mr->medication->medications[0]->price == 8);
  repository_destructor(mr);

  return 0;
}
