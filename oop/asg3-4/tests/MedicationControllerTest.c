#include <stdio.h>
#include <assert.h>
#include "../controller/MedicationController.h"
#include "../history/HistoryController.h"
#include "../ds/Vector.h"

int main() {
  char n1[] = "asdf";
  char n2[] = "aerty";
  char substr1[] = "sd";
  char substr2[] = "z";
  char substr3[] = "";
  char substr4[] = "a";

  HistoryController* hc = history_controller_init();
  MedicationController* mc = controller_init(hc);

  controller_addMedication(mc, n1, 3, 5, 4);
  controller_addMedication(mc, n1, 3, 3, 2);

  assert(controller_getAll(mc)->size == 1);
  controller_addMedication(mc, n2, 2, 6, 7);
  Vector* ans1 = controller_getAll(mc);
  assert(ans1->size == 2);

  Vector* ans2 = controller_findByStr(mc, substr1, 1);
  assert(ans2->size == 1);

  Vector* ans6 = controller_findByStr(mc, substr2, 1);
  assert(ans6->size == 0);

  Vector* ans8 = controller_findByStr(mc, substr4, 1);
  assert(ans8->size == 2);

  Vector* ans7 = controller_findByStr(mc, substr3, 1);
  assert(ans7->size == 2);

  controller_deleteMedication(mc, n2, 2);
  Vector* ans3 = controller_getAll(mc);
  assert(ans3->size == 1);

  controller_updateMedicationQuantity(mc, n1, 3, 2);
  Vector* ans4 = controller_getAll(mc);
  assert(((Medication*)vector_get(ans4, 0))->quantity == 10);

  controller_updateMedicatonPrice(mc, n1, 3, -2);
  assert(((Medication*)mc->repo->medication->items[0])->price == 2);
  Vector* ans5 = controller_getAll(mc);
  assert(((Medication*)vector_get(ans5, 0))->price == 2);

  free(ans2->items);
  free(ans2);
  free(ans6->items);
  free(ans6);
  free(ans7->items);
  free(ans7);
  free(ans8->items);
  free(ans8);

  controller_destructor(mc);
  return 0;
}
