#include <ctype.h>
#include <string.h>
#include "MedicationListController.h"
#include "../../history/list/HistoryListController.h"
#include "../../ds/Vector.h"


MedicationListController* list_controller_init(HistoryListController* hc) {
  MedicationListController* mc = (MedicationListController*)malloc(sizeof(MedicationListController));
  MedicationRepository* mr = repository_init();
  mc->repo = mr;
  mc->history = hc;

  return mc;
}


Vector* list_controller_shortSupply(MedicationListController* mc, int x) {
  Vector* ans = vector_init();
  Vector* all = repository_getAll(mc->repo);

  int i;
  for(i=0; i<all->size; i++) {
    Medication* m = (Medication*)vector_get(all, i);
    if(m->quantity < x) {
      vector_add(ans, copy_medication(m));
    }
  }

  return ans;
}


Vector* list_controller_highPrice(MedicationListController* mc, double p) {
  Vector* ans = vector_init();
  Vector* all = repository_getAll(mc->repo);

  int i;
  for(i=0; i<all->size; i++) {
    Medication* m = (Medication*)vector_get(all, i);
    if(m->quantity > p) {
      vector_add(ans, copy_medication(m));
    }
  }

  return ans;
}


Vector* list_controller_findByStr(MedicationListController* mc, char* sstr, int sort_asc) {
  Vector* ans = vector_init();

  if(strlen(sstr) == 0) {
    int i=0;
    for(i=0; i<mc->repo->medication->size; i++) {
      Medication* m = (Medication*)vector_get(mc->repo->medication, i);
      vector_add(ans, m);
    }
  }
  else {
    int i;
    for(i=0; i<mc->repo->medication->size; i++) {
      Medication* m = (Medication*)vector_get(mc->repo->medication, i);
      char* lower = (char*)malloc(strlen(m->name)+1);
      strcpy(lower, m->name);
      char* p = lower;
      for(; *p != 0; p++) *p = tolower(*p);
      if(strstr(lower, sstr) != NULL) {
        vector_add(ans, m);

      }
      free(lower);
    }
  }

  int (*sort_f)(const void* a, const void* b) = (sort_asc) ? sort_ascending:sort_descending;
  qsort(ans->items, ans->size, sizeof(Medication*), sort_f);

  return ans;
}


void list_controller_addMedication(MedicationListController* mc, char* n, double c, int q, double p) {
  Medication* m = medication_init(n, c, q, p);
  history_list_controller_addUndo(mc->history, mc->repo);
  repository_addMedication(mc->repo, m);
}


void list_controller_deleteMedication(MedicationListController* mc, char* n, double c) {
  history_list_controller_addUndo(mc->history, mc->repo);
  repository_deleteMedication(mc->repo, n, c);
}


void list_controller_updateMedicationQuantity(MedicationListController* mc, char* n, double c, int nq) {
  history_list_controller_addUndo(mc->history, mc->repo);
  repository_updateMedicationQuantity(mc->repo, n, c, nq);
}


Vector* list_controller_getAll(MedicationListController* mc) {
  return repository_getAll(mc->repo);
}


void list_controller_undo(MedicationListController* mc) {
  MedicationRepository* undo = (MedicationRepository*)vector_get(mc->history->undo, mc->history->undo->size-1);
  history_list_controller_addRedo(mc->history, mc->repo);
  repository_destructor(mc->repo);
  mc->repo = undo;
  mc->history->undo->items[mc->history->undo->size-1] = NULL;
  mc->history->undo->size -= 1;
}


void list_controller_redo(MedicationListController* mc) {
  MedicationRepository* redo = (MedicationRepository*)vector_get(mc->history->redo, mc->history->redo->size-1);
  history_list_controller_addUndo(mc->history, mc->repo);
  repository_destructor(mc->repo);
  mc->repo = redo;
  mc->history->redo->items[mc->history->redo->size-1] = NULL;
  mc->history->redo->size -= 1;
}


void list_controller_destructor(MedicationListController* mc) {
  repository_destructor(mc->repo);
  history_list_controller_destructor(mc->history);
  free(mc);
}
