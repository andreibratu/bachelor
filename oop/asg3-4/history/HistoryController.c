#include <stdlib.h>
#include <string.h>
#include "HistoryController.h"
#include "../repo/MedicationRepository.h"
#include "../model/Action.h"
#include "../ds/Vector.h"


HistoryController* history_controller_init() {
  HistoryController* hc = (HistoryController*)malloc(sizeof(HistoryController));
  hc->undo = vector_init();
  hc->redo = vector_init();

  return hc;
}


void history_controller_addUndo(HistoryController* hc, Action* a) {
  vector_add(hc->undo, a);
}


void history_controller_addRedo(HistoryController* hc, Action* a) {
  vector_add(hc->redo, a);
}


void history_controller_applyUndo(HistoryController* hc, MedicationRepository* mr) {
  Action* a = (Action*)vector_get(hc->undo, hc->undo->size-1);
  Action* redo = action_init(-1, a->name, a->concentration, a->quantity, a->price, a->amount);
  Medication* m = medication_init(a->name, a->concentration, a->quantity, a->price);

  switch (a->type) {
    case ADD:
      redo->type = DELETE;
      repository_addMedication(mr, m);
      break;
    case DELETE:
      redo->type = ADD;
      repository_deleteMedication(mr, a->name, a->concentration);
      break;
    case UPDATEQ:
      redo->type = UPDATEQ;
      repository_updateMedicationQuantity(mr, a->name, a->concentration, a->amount);
      redo->amount *= -1;
      break;
    case UPDATEP:
      redo->type = UPDATEP;
      repository_updateMedicationPrice(mr, a->name, a->concentration, a->amount);
      redo->amount *= -1;
      break;
  }

  history_controller_addRedo(hc, redo);
  medication_destructor(m);
  void (*destructor)(TElem) = (void(*)(TElem)) action_destructor;
  vector_remove(hc->undo, hc->undo->size-1, destructor);
}


void history_controller_applyRedo(HistoryController* hc, MedicationRepository* mr) {
  Action* a = (Action*)vector_get(hc->redo, hc->redo->size-1);
  Action* undo = action_init(-1, a->name, a->concentration, a->quantity, a->price, a->amount);
  Medication* m = medication_init(a->name, a->concentration, a->quantity, a->price);

  switch (a->type) {
    case ADD:
      repository_addMedication(mr, m);
      undo->type = DELETE;
      break;
    case DELETE:
      undo->type = ADD;
      repository_deleteMedication(mr, a->name, a->concentration);
      break;
    case UPDATEQ:
      repository_updateMedicationQuantity(mr, a->name, a->concentration, a->amount);
      undo->type = UPDATEQ;
      undo->amount *= -1;
      break;
    case UPDATEP:
      repository_updateMedicationPrice(mr, a->name, a->concentration, a->amount);
      undo->type = UPDATEP;
      undo->amount *= -1;
      break;
  }

  history_controller_addUndo(hc, undo);
  medication_destructor(m);
  void (*destructor)(TElem) = (void (*)(TElem)) action_destructor;
  vector_remove(hc->redo, hc->redo->size-1, destructor);
}


void history_controller_destructor(HistoryController* hc) {
  void (*destructor)(TElem) = (void(*)(TElem)) action_destructor;
  vector_destructor(hc->undo, destructor);
  vector_destructor(hc->redo, destructor);
  free(hc);
}
