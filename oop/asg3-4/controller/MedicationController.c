#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "MedicationController.h"
#include "../history/HistoryController.h"
#include "../model/Action.h"


MedicationController* controller_init(HistoryController* hc) {
  MedicationController* mc = (MedicationController*)malloc(sizeof(MedicationController));
  MedicationRepository* mr = repository_init();
  mc->repo = mr;
  mc->history = hc;
  return mc;
}


MedicationVector* controller_shortSupply(MedicationController* mc, int x) {
  MedicationVector* ans = vector_init();
  MedicationVector* all = repository_getAll(mc->repo);

  int i;
  for(i=0; i<all->size; i++) {
    if(all->medications[i]->quantity < x) {
      vector_add(ans, all->medications[i]);
    }
  }

  return ans;
}


MedicationVector* controller_highPrice(MedicationController* mc, double p) {
  MedicationVector* ans = vector_init();
  MedicationVector* all = repository_getAll(mc->repo);

  int i;
  for(i=0; i<all->size; i++) {
    if(all->medications[i]->price > p) {
      vector_add(ans, all->medications[i]);
    }
  }

  return ans;
}


MedicationVector* controller_findByStr(MedicationController* mc, char* sstr, int flag) {
  MedicationVector* ans = vector_init();
  MedicationVector* all = repository_getAll(mc->repo);

  if(strlen(sstr) == 0) {
    ans = all;
  }
  else {
    int i;
    for(i=0; i<all->size; i++) {
      char* lower = (char*)malloc(strlen(all->medications[i]->name)+1);
      strcpy(lower, all->medications[i]->name);
      char* p = lower;
      for(; *p != 0; p++) *p = tolower(*p);
      if(strstr(lower, sstr) != NULL) {
        vector_add(ans, all->medications[i]);
      }
    }
  }

  if(!flag)
    qsort(ans->medications, ans->size, sizeof(Medication*), sort_descending);
  else
    qsort(ans->medications, ans->size, sizeof(Medication*), sort_ascending);
  return ans;
}


MedicationVector* controller_getAll(MedicationController* mc) {
MedicationVector* all = repository_getAll(mc->repo);

  return all;
}


void controller_addMedication(MedicationController* mc, char* n, double c, int q, double p) {
  Medication* m = medication_init(n, c, q, p);
  char undo_action[] = "delete";
  Action* undo = action_init(undo_action, n, c, q, p, -1);
  history_controller_addUndo(mc->history, undo);
  return repository_addMedication(mc->repo, m);
}


void controller_deleteMedication(MedicationController* mc, char* n, double c) {
  repository_deleteMedication(mc->repo, n, c);
  // char undo_action = "add";
}


void controller_updateMedicationQuantity(MedicationController* mc, char* n, double c, int nq) {
  repository_updateMedicationQuantity(mc->repo, n, c, nq);
  char undo_action[] = "updateQ";
  Action* undo = action_init(undo_action, n, c, -1, -1, -nq);
  history_controller_addUndo(mc->history, undo);
}


void controller_updateMedicatonPrice(MedicationController* mc, char* n, double c, double np) {
  repository_updateMedicationPrice(mc->repo, n, c, np);
  char undo_action[] = "updateP";
  Action* undo = action_init(undo_action, n, c, -1, -1, -np);
  history_controller_addUndo(mc->history, undo);
}


// void controller_undo(MedicationController* mc) {
//   history_controller_apply(mc->history, mc->history->undo, mc->repo);
// }


void controller_destructor(MedicationController* mc) {
  repository_destructor(mc->repo);
  free(mc);
}
