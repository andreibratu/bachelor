#ifndef MEDICATION_REPOSITORY_H
#define MEDICATION_REPOSITORY_H

#include "../ds/MedicationVector.h"

typedef struct {
  MedicationVector* medication;
} MedicationRepository;

MedicationRepository* repository_init();

void addMedication(MedicationRepository*, char*, double, int, double);

void deleteMedication(MedicationRepository*, char*, double);

void updateMedicationQuantity(MedicationRepository*, char*, double, int);

void updateMedicationPrice(MedicationRepository*, char*, double, double);

void repository_destructor(MedicationRepository*);

MedicationVector* getAll(MedicationRepository*);

#endif
