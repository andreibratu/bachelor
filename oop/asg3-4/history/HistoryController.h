#ifndef HISTORY_CONTROLLER
#define HISTORY_CONTROLLER

#include "../repo/MedicationRepository.h"
#include "../ds/Vector.h"
#include "../model/Action.h"


typedef struct {
  Vector* undo;
  Vector* redo;
} HistoryController;


HistoryController* history_controller_init();

void history_controller_addUndo(HistoryController*, Action*);

void history_controller_addRedo(HistoryController*, Action*);

void history_controller_applyUndo(HistoryController*, MedicationRepository* mr);

void history_controller_applyRedo(HistoryController*, MedicationRepository* mr);

void history_controller_destructor(HistoryController*);

#endif
