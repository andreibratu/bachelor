#include "./HistoryController.h"
#include "../repo/MedicationRepository.h"
#include "../model/Action.h"
#include "../ds/ActionVector.h"
#include <stdlib.h>
#include <string.h>


HistoryController* history_controller_init() {
  HistoryController* hc = (HistoryController*)malloc(sizeof(HistoryController));
  hc->undo = action_vector_init();
  hc->redo = action_vector_init();

  return hc;
}

void history_controller_addUndo(HistoryController* hc, Action* a) {
  action_vector_add(hc->undo, a);
}


void history_controller_addRedo(HistoryController* hc, Action* a) {
  action_vector_add(hc->redo, a);
}


void history_controller_apply(HistoryController* hc, ActionVector* av, MedicationRepository* mr) {
  Action* a = av->actions[0];

  if(strcmp(a->name, "add") == 0) {
    char new_action[] = "delete";
    Action* redo = action_init(new_action, a->name, a->concentration, -1, -1, -1);
    history_controller_addRedo(hc, redo);
  }

  if(strcmp(a->name, "delete") == 0) {
    char new_action[] = "add";
    Action* redo = action_init(new_action, a->name, a->concentration, a->quantity, a->price, a->amount);
    history_controller_addRedo(hc, redo);
  }

  if(strcmp(a->name, "updateQ") == 0) {
    char new_action[] = "updateQ";
    Action* redo = action_init(new_action, a->name, a->concentration, -a->quantity, a->price, a->amount);
    history_controller_addRedo(hc, redo);
  }

  if(strcmp(a->name, "updateP") == 0) {
    char new_action[] = "updateP";
    Action* redo = action_init(new_action, a->name, a->concentration, a->quantity, -a->price, a->amount);
    history_controller_addRedo(hc, redo);
  }


  if(strcmp(a->action, "delete") == 0) {
    repository_deleteMedication(mr, a->name, a->concentration);
  }

  if(strcmp(a->action, "add") == 0) {
    Medication* m = medication_init(a->name, a->concentration, a->quantity, a->price);
    repository_addMedication(mr, m);
  }

  if(strcmp(a->action, "updateQ") == 0) {
    repository_updateMedicationQuantity(mr, a->name, a->concentration, a->amount);
  }

  if(strcmp(a->action, "updateP") == 0) {
    repository_updateMedicationPrice(mr, a->name, a->concentration, a->amount);
  }
}
