#include "MedicationRepository.h"
#include "../ds/Vector.h"
#include "../model/Medication.h"
#include <stdlib.h>


MedicationRepository* repository_init() {
  MedicationRepository* mr = (MedicationRepository*)malloc(sizeof(MedicationRepository));
  mr->medication = vector_init();
  return mr;
}


int repository_find_medication(vector* v, char* name, double concentration) {
  int i;
  for(i=0; i<v->size; i++) {
    Medication* m = (Medication*)vector_get(v, i);
    if(same(m, name, concentration)) {
      return i;
    }
  }
  return -1;
}


void repository_addMedication(MedicationRepository* mr, Medication* m) {
  int idx = repository_find_medication(mr->medication, m->name, m->concentration);

  if(idx == -1) {
    vector_add(mr->medication, m);
  }

  Medication* existent = (Medication*)vector_get(mr->medication, idx);
  existent->quantity += m->quantity;
}


void repository_deleteMedication(MedicationRepository* mr, char* name, double c) {
  int idx = repository_find_medication(mr->medication, name, c);
  if(idx == -1) return;
  vector_delete(mr->medication, idx);
}


void repository_updateMedicationQuantity(MedicationRepository* mr, char* name, double c, int q) {
  int idx = repository_find_medication(mr->medication, name, c);
  if(idx == -1) return;
  ((Medication*)vector_get(mr->medication, idx))->quantity += q;
}


void repository_updateMedicationPrice(MedicationRepository* mr, char* name, double c, double p) {
  int idx = repository_find_medication(mr->medication, name, c);
  if(idx == -1) return;
  ((Medication*)vector_get(mr->medication, idx))->price += p;
}


  vector* repository_getAll(MedicationRepository* mr) {
  return mr->medication;
}


void repository_destructor(MedicationRepository* mr) {
  vector_free(mr->medication);
  free(mr);
}
