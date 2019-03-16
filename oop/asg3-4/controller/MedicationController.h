#ifndef MEDICATION_CONTROLLER_H
#define MEDICATION_CONTROLLER_H

#include "../repo/MedicationRepository.h"
#include <stdlib.h>

typedef struct {
  MedicationRepository* repo;
} MedicationController;

MedicationController* controller_init();

MedicationVector* controller_getAll(MedicationController*);

void controller_addMedication(MedicationController*, char*, double, int, double);

void controller_deleteMedication(MedicationController*, char*, double);

void controller_updateMedicationQuantity(MedicationController*, char*, double, int);

void controller_updateMedicatonPrice(MedicationController*, char*, double, double);

MedicationVector* controller_shortSupply(MedicationController*, int);

MedicationVector* controller_highPrice(MedicationController*, double);

MedicationVector* controller_findByStr(MedicationController*, char*, int);

void controller_destructor(MedicationController*);

#endif
