#ifndef MEDICATION_VECTOR_H
#define MEDICATION_VECTOR_H

#include "../model/Medication.h"


typedef struct {
  Medication* medications;
  int size;
  int capacity;
} MedicationVector;


MedicationVector* init(int);

void add(MedicationVector*, Medication);

void remove(MedicationVector*, char*, double);

void destroy(MedicationVector*);

#endif
