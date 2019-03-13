#ifndef MEDICATION_VECTOR_H
#define MEDICATION_VECTOR_H

#include "../model/Medication.h"


typedef struct {
  Medication** medications;
  int size;
  int capacity;
} MedicationVector;


MedicationVector* vector_init(int);

void vector_add(MedicationVector*, Medication*);

int vector_find(MedicationVector*, char*, double);

void vector_remove(MedicationVector*, char*, double);

void vector_destructor(MedicationVector*);

#endif
