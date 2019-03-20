#include <stdio.h>
#include <assert.h>
#include "../controller/MedicationController.h"
#include "../history/HistoryController.h"

int main() {
  HistoryController* hc = history_controller_init();
  MedicationController* mc = controller_init(hc);

  char n1[] = "asdf";

  controller_addMedication(mc, n1, 3, 5, 4);
  assert(mc->history->undo->size == 1);
  assert(mc->history->redo->size == 0);
  controller_undo(mc);
  assert(mc->history->undo->size == 0);
  assert(controller_getAll(mc)->size == 0);
  assert(mc->history->redo->size == 1);
  controller_redo(mc);
  assert(controller_getAll(mc)->size == 1);
  assert(mc->history->redo->size == 0);
  assert(mc->history->undo->size == 1);
  controller_destructor(mc);
}
