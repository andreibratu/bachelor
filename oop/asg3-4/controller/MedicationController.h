#ifndef MEDICATION_CONTROLLER_H
#define MEDICATION_CONTROLLER_H

#include "../repo/MedicationRepository.h"
#include "../history/HistoryController.h"
#include "../ds/Vector.h"
#include <stdlib.h>

typedef struct {
  // Object implementing business logic of the application
  MedicationRepository* repo;
  HistoryController* history;
  void* ans;
} MedicationController;

// Constructor
MedicationController* controller_init(HistoryController*);

// Return all Medication
Vector* controller_getAll(MedicationController*);

// Construct and add new Medication object
void controller_addMedication(MedicationController*, char*, double, int, double);

// Delete Medication identified by name and concentration
void controller_deleteMedication(MedicationController*, char*, double);

// Update quantity incrementally (see repo doc)
void controller_updateMedicationQuantity(MedicationController*, char*, double, int);

// Update price incrementally (see repo doc)
void controller_updateMedicatonPrice(MedicationController*, char*, double, double);

// Return all medication whose quantity is smaller than given bound
Vector* controller_shortSupply(MedicationController*, int);

// Return all medication whose price is larger than given bound
Vector* controller_highPrice(MedicationController*, double);

// Find all Medication whose name contains given substring, case-insensitive
// List of objects can be sorted ascendingly or descendingy (see Medication.h)
Vector* controller_findByStr(MedicationController*, char*, int);

void controller_undo(MedicationController*);

void controller_redo(MedicationController*);

// Destructor
void controller_destructor(MedicationController*);


#endif
