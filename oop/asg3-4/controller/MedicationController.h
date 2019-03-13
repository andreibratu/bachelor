#ifndef MEDICATION_CONTROLLER_H
#define MEDICATION_CONTROLLER_H

#include "../repo/MedicationRepository.h"

typedef struct {
  MedicationRepository* repo;
} MedicationController;


MedicationVector* shortSupply(MedicationController*, int);

MedicationVector* findByStr(MedicationController*, char*);

MedicationVector* getAll(MedicationController*);

void add(MedicationController*, char*, double, int, double);

void controllerAddMedication(MedicationController*, char*, double, int, double);

void deleteMedication(MedicationController*, char*, double);

void updateMedicationQuantity(MedicationController*, )

#endif
