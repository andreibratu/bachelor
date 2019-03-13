#include "MedicationRepository.h"
#include "../ds/MedicationVector.h"
#include "../model/Medication.h"
#include <stdlib.h>


MedicationRepository* repository_init() {
  MedicationRepository* mr = (MedicationRepository*)malloc(sizeof(MedicationRepository));
  mr->medication = medication_vector_init(1);

  return mr;
}


void addMedication(MedicationRepository* mr, Medication* m) {
  int idx = find(mr->medication, m->name, m->concentration);
  if(idx != -1) mr->medication->medications[idx]->quantity += m->quantity;
  else {
    add(mr->medication, m);
  }
}


void deleteMedication(MedicationRepository* mr, char* name, double c) {
  removeMedication(mr->medication, name, c);
}


void updateMedicationQuantity(MedicationRepository* mr, char* name, double c, int q) {
  int idx = find(mr->medication, name, c);
  if(idx == -1) return;
  mr->medication->medications[idx]->quantity += q;
}


void updateMedicationPrice(MedicationRepository* mr, char* name, double c, double p) {
  int idx = find(mr->medication, name, c);
  if(idx == -1) return;
  mr->medication->medications[idx]->price += p;
}


void repository_destructor(MedicationRepository* mr) {
  medication_vector_destructor(mr->medication);
  free(mr);
}


MedicationVector* getAll(MedicationRepository* mr) {
  return mr->medication;
}
