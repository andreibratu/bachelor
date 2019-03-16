#ifndef MEDICATION_CONTROLLER_H
#define MEDICATION_CONTROLLER_H

#include "../repo/MedicationRepository.h"
#include <stdlib.h>

typedef struct {
  // Object implementing business logic of the application
  MedicationRepository* repo;
} MedicationController;

// Constructor
MedicationController* controller_init();

// Return all Medication
MedicationVector* controller_getAll(MedicationController*);

// Construct and add new Medication object
void controller_addMedication(MedicationController*, char*, double, int, double);

// Delete Medication identified by name and concentration
void controller_deleteMedication(MedicationController*, char*, double);

// Update quantity incrementally (see repo doc)
void controller_updateMedicationQuantity(MedicationController*, char*, double, int);

// Update price incrementally (see repo doc)
void controller_updateMedicatonPrice(MedicationController*, char*, double, double);

// Return all medication whose quantity is smaller than given bound
MedicationVector* controller_shortSupply(MedicationController*, int);

// Return all medication whose price is larger than given bound
MedicationVector* controller_highPrice(MedicationController*, double);

// Find all Medication whose name contains given substring, case-insensitive
// List of objects can be sorted ascendingly or descendingy (see Medication.h)
MedicationVector* controller_findByStr(MedicationController*, char*, int);

// Destructor
void controller_destructor(MedicationController*);

#endif
