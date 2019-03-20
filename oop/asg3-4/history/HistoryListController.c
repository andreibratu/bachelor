#include <stdlib.h>
#include "HistoryListController.h"


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
    Medication* m = copy_medication((Medication*)r->medication->items[i]);
    repository_addMedication(undo_repo, m);
  }
  vector_add(hc->undo, undo_repo);
}


void history_list_controller_addRedo(HistoryListController* hc, MedicationRepository* r) {
  MedicationRepository* redo_repo = repository_init();
  int i;
  for(i=0; i<r->medication->size; i++) {
    Medication* m = copy_medication((Medication*)r->medication->items[i]);
    repository_addMedication(redo_repo, m);
  }
  vector_add(hc->redo, redo_repo);
}


void history_list_controller_applyUndo(HistoryListController* hc, MedicationController* mc) {
  MedicationRepository* undo = (MedicationRepository*)vector_get(hc->undo, hc->undo->size-1);
  history_list_controller_addRedo(hc, mc->repo);
  repository_destructor(mc->repo);
  mc->repo = undo;
  hc->undo->items[hc->undo->size-1] = NULL;
  hc->undo->size -= 1;
}


void history_list_controller_applyRedo(HistoryListController* hc, MedicationController* mc) {
  MedicationRepository* redo = (MedicationRepository*)vector_get(hc->redo, hc->redo->size-1);
  history_list_controller_addUndo(hc, mc->repo);
  repository_destructor(mc->repo);
  mc->repo = redo;
  hc->redo->items[hc->redo->size-1] = NULL;
  hc->redo->size -= 1;
}


void history_list_controller_destructor(HistoryListController* hc) {
  void (*destructor)(TElem) = (void(*)(TElem)) repository_destructor;
  vector_destructor(hc->undo, destructor);
  vector_destructor(hc->redo, destructor);
}
