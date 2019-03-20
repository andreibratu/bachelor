#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "MedicationController.h"
#include "../history/HistoryController.h"
#include "../ds/Vector.h"
#include "../model/Action.h"



MedicationController* controller_init(HistoryController* hc) {
  MedicationController* mc = (MedicationController*)malloc(sizeof(MedicationController));
  MedicationRepository* mr = repository_init();
  mc->repo = mr;
  mc->history = hc;
  return mc;
}


Vector* controller_shortSupply(MedicationController* mc, int x) {
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


Vector* controller_highPrice(MedicationController* mc, double p) {
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


Vector* controller_findByStr(MedicationController* mc, char* sstr, int sort_asc) {
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


void controller_addMedication(MedicationController* mc, char* n, double c, int q, double p) {
  Medication* m = medication_init(n, c, q, p);
  Action* undo = action_init(DELETE, n, c, q, p, -1);
  history_controller_addUndo(mc->history, undo);
  repository_addMedication(mc->repo, m);
}


void controller_deleteMedication(MedicationController* mc, char* n, double c) {
  int idx = repository_find_medication(mc->repo, n, c);
  Medication* m = (Medication*)vector_get(mc->repo->medication, idx);
  Action* undo = action_init(ADD, m->name, m->concentration, m->quantity, m->price, -1);
  history_controller_addUndo(mc->history, undo);
  repository_deleteMedication(mc->repo, n, c);
}


void controller_updateMedicationQuantity(MedicationController* mc, char* n, double c, int nq) {
  repository_updateMedicationQuantity(mc->repo, n, c, nq);
  Action* undo = action_init(UPDATEQ, n, c, -1, -1, -nq);
  history_controller_addUndo(mc->history, undo);
}


void controller_updateMedicatonPrice(MedicationController* mc, char* n, double c, double np) {
  repository_updateMedicationPrice(mc->repo, n, c, np);
  Action* undo = action_init(UPDATEP, n, c, -1, -1, -np);
  history_controller_addUndo(mc->history, undo);
}


Vector* controller_getAll(MedicationController* mc) {
  return repository_getAll(mc->repo);
}


void controller_undo(MedicationController* mc) {
  history_controller_applyUndo(mc->history, mc->repo);
}


void controller_redo(MedicationController* mc) {
  history_controller_applyRedo(mc->history, mc->repo);
}


void controller_destructor(MedicationController* mc) {
  repository_destructor(mc->repo);
  history_controller_destructor(mc->history);
  free(mc);
}
