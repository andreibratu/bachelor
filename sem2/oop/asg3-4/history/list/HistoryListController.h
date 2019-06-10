#ifndef HISTORY_L_CONTROLLER
#define HISTORY_L_CONTROLLER

#include "../../ds/Vector.h"
#include "../../repo/MedicationRepository.h"


typedef struct {
  Vector* undo;
  Vector* redo;
} HistoryListController;

HistoryListController* history_list_controller_init();

void history_list_controller_addUndo(HistoryListController*, MedicationRepository*);

void history_list_controller_addRedo(HistoryListController*, MedicationRepository*);

void history_list_controller_destructor(HistoryListController*);

#endif
