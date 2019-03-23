#include <stdlib.h>
#include "HistoryListController.h"
#include "../../controller/list/MedicationListController.h"


HistoryListController* history_list_controller_init() {
  HistoryListController* hc = (HistoryListController*)malloc(sizeof(HistoryListController));
  hc->undo = vector_init();
  hc->redo = vector_init();
  return hc;
}


void history_list_controller_addUndo(HistoryListController* hc, MedicationRepository* r) {
  MedicationRepository* undo_repo = repository_init();
  int i;
  for(i=0; i<r->medication->size; i++) {
    Medication* m = copy_medication((Medication*)vector_get(r->medication, i));
    repository_addMedication(undo_repo, m);
  }
  vector_add(hc->undo, undo_repo);
}


void history_list_controller_addRedo(HistoryListController* hc, MedicationRepository* r) {
  MedicationRepository* redo_repo = repository_init();
  int i;
  for(i=0; i<r->medication->size; i++) {
    Medication* m = copy_medication((Medication*)vector_get(r->medication, i));
    repository_addMedication(redo_repo, m);
  }
  vector_add(hc->redo, redo_repo);
}


void history_list_controller_destructor(HistoryListController* hc) {
  void (*destructor)(TElem) = (void(*)(TElem)) repository_destructor;
  vector_destructor(hc->undo, destructor);
  vector_destructor(hc->redo, destructor);
}
