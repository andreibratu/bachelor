#ifndef MEDICATION_REPOSITORY_H
#define MEDICATION_REPOSITORY_H

#include "../ds/MedicationVector.h"

typedef struct {
  MedicationVector* medication;
} MedicationRepository;

MedicationRepository* init();

void addMedication(MedicationRepository*, Medication);

void deleteMedication(MedicationRepository*, char*, double);

void updateMedication(MedicationRepository*, char*, double*, int);



#endif
