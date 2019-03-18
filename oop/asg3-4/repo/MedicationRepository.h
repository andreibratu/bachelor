#ifndef MEDICATION_REPOSITORY_H
#define MEDICATION_REPOSITORY_H

#include "../ds/Vector.h"
#include "../model/Medication.h"

typedef struct {
  // Object delegated with keeping the objects
  vector* medication;
} MedicationRepository;

MedicationRepository* repository_init();

int repository_find_medication(vector*, char*, double);

// Add medication to repository
// Medication will be uniquely identified by name and concentration
// If a new Medication is a duplicate by these criteria, its quantity
// will be added to the already existing one
void repository_addMedication(MedicationRepository*, Medication* m);

// Delete medication from repository
void repository_deleteMedication(MedicationRepository*, char*, double);

// Update quantity of given Medication
// Update is done incrementally, so arg is added to existing quantity
void repository_updateMedicationQuantity(MedicationRepository*, char*, double, int);

// Update price incrementally, see above
void repository_updateMedicationPrice(MedicationRepository*, char*, double, double);

// Return all Medication objects in a Vector
vector* repository_getAll(MedicationRepository*);

// Repository destructor
void repository_destructor(MedicationRepository*);

#endif
