#include "MedicationRepository.h"
#include "../ds/MedicationVector.h"
#include "../model/Medication.h"
#include <stdlib.h>


MedicationRepository* repository_init() {
  MedicationRepository* mr = (MedicationRepository*)malloc(sizeof(MedicationRepository));
  mr->medication = vector_init();

  return mr;
}


void repository_addMedication(MedicationRepository* mr, Medication* m) {
  int idx = vector_find(mr->medication, m->name, m->concentration);
  if(idx != -1) mr->medication->medications[idx]->quantity += m->quantity;
  else {
    vector_add(mr->medication, m);
  }
}


void repository_deleteMedication(MedicationRepository* mr, char* name, double c) {
  vector_remove(mr->medication, name, c);
}


void repository_updateMedicationQuantity(MedicationRepository* mr, char* name, double c, int q) {
  int idx = vector_find(mr->medication, name, c);
  if(idx == -1) return;
  mr->medication->medications[idx]->quantity += q;
}


void repository_updateMedicationPrice(MedicationRepository* mr, char* name, double c, double p) {
  int idx = vector_find(mr->medication, name, c);
  if(idx == -1) return;
  mr->medication->medications[idx]->price += p;
}


  MedicationVector* repository_getAll(MedicationRepository* mr) {
  return mr->medication;
}


void repository_destructor(MedicationRepository* mr) {
  vector_destructor(mr->medication);
  free(mr);
}
