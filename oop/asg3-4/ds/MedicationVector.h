#ifndef MEDICATION_VECTOR_H
#define MEDICATION_VECTOR_H

#include "../model/Medication.h"


typedef struct {
  // Dynamic array implementation for Medication
  // This will be replaced with an universal dynamic container
  Medication** medications;
  int size;
  int capacity;
} MedicationVector;


MedicationVector* vector_init();

// Add object to the container, increasing capacity if necessary
void vector_add(MedicationVector*, Medication*);

// Find Medication by name and concentration
int vector_find(MedicationVector*, char*, double);

// Find and remove Medication
void vector_remove(MedicationVector*, char*, double);

void vector_destructor(MedicationVector*);

#endif
