#ifndef MEDICATION_CONTROLLER_H
#define MEDICATION_CONTROLLER_H

#include "../repo/MedicationRepository.h"

typedef struct {
  MedicationRepository* repo;
} MedicationController;


MedicationVector* short_supply(MedicationController*, int);

MedicationVector* find(MedicationController*, char*); 


#endif
