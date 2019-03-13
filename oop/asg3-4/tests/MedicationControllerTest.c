#include <assert.h>
#include "../model/Medication.h"
#include "../controller/MedicationController.h"

int main() {
  char n1[] = "asdf";
  char n2[] = "erty";
  char substr1[] = "sd";

  MedicationController* mc = controller_init();

  controller_vector_repository_addMedication(mc, n1, 3, 5, 4);
  controller_vector_repository_addMedication(mc, n1, 3, 3, 2);
  assert(controller_getAll(mc)->size == 1);
  controller_vector_repository_addMedication(mc, n2, 2, 6, 7);
  assert(controller_getAll(mc)->size == 2);
  assert(controller_findByStr(mc, substr1)->size != 0);
  controller_deleteMedication(mc, n2, 2);
  assert(controller_getAll(mc)->size == 1);
  controller_updateMedicationQuantity(mc, n1, 3, 2);
  assert(controller_getAll(mc)->medications[0]->quantity == 10);
  controller_updateMedicatonPrice(mc, n1, 3, -2);
  assert(controller_getAll(mc)->medications[0]->price == 2);
  controller_destructor(mc);
  return 0;
}
