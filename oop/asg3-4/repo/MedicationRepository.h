#ifndef MEDICATION_REPOSITORY_H
#define MEDICATION_REPOSITORY_H

#include "../ds/MedicationVector.h"

typedef struct {
  MedicationVector* medication;
} MedicationRepository;

MedicationRepository* repository_init();

void repository_addMedication(MedicationRepository*, Medication* m);

void repository_deleteMedication(MedicationRepository*, char*, double);

void repository_updateMedicationQuantity(MedicationRepository*, char*, double, int);

void repository_updateMedicationPrice(MedicationRepository*, char*, double, double);

void repository_destructor(MedicationRepository*);

MedicationVector* repository_getAll(MedicationRepository*);

#endif
