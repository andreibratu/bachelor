#ifndef MEDICATION_L_CONTROLLER_H
#define MEDICATION_L_CONTROLLER_H

#include "../../repo/MedicationRepository.h"
#include "../../history/list/HistoryListController.h"
#include "../../ds/Vector.h"
#include <stdlib.h>

typedef struct {
  // Object implementing business logic of the application
  MedicationRepository* repo;
  HistoryListController* history;
} MedicationListController;


MedicationListController* list_controller_init(HistoryListController*);

Vector* list_controller_getAll(MedicationListController*);

void list_controller_addMedication(MedicationListController*, char*, double, int, double);

void list_controller_deleteMedication(MedicationListController*, char*, double);

void list_controller_updateMedicationQuantity(MedicationListController*, char*, double, int);

void list_controller_updateMedicationPrice(MedicationListController*, char*, double, double);

Vector* list_controller_shortSupply(MedicationListController*, int);

Vector* list_controller_highPrice(MedicationListController*, double);

Vector* list_controller_findByStr(MedicationListController*, char*, int);

void list_controller_undo(MedicationListController*);

void list_controller_redo(MedicationListController*);

void list_controller_destructor(MedicationListController*);

#endif
