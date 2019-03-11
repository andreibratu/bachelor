#ifndef MEDICATION_VECTOR_H
#define MEDICATION_VECTOR_H

#include "../model/Medication.h"


typedef struct {
  Medication** medications;
  int size;
  int capacity;
} MedicationVector;


MedicationVector* medication_vector_init(int);

void add(MedicationVector*, Medication*);

int find(MedicationVector*, char*, double);

void remove(MedicationVector*, char*, double);

void medication_vector_destructor(MedicationVector*);

#endif
