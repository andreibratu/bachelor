#include <stdio.h>
#include <stdlib.h>
#include "MedicationRepository.h"
#include "../ds/Vector.h"
#include "../model/Medication.h"


MedicationRepository* repository_init() {
  MedicationRepository* mr = (MedicationRepository*)malloc(sizeof(MedicationRepository));
  mr->medication = vector_init();
  return mr;
}


int repository_find_medication(MedicationRepository* mr, char* n, double c) {
  Medication* key = medication_init(n, c, -1, -1);
  int (*find)(TElem, TElem) = (int (*)(TElem, TElem)) medication_equal;
  int idx = vector_find(mr->medication, key, find);
  medication_destructor(key);
  return idx;
}


void repository_addMedication(MedicationRepository* mr, Medication* m) {
  int idx = repository_find_medication(mr, m->name, m->concentration);

  if(idx == -1) {
    vector_add(mr->medication, m);
    return;
  }

  Medication* existent = (Medication*)vector_get(mr->medication, idx);
  medication_destructor(m);
  existent->quantity += m->quantity;
}


void repository_deleteMedication(MedicationRepository* mr, char* name, double c) {
  int idx = repository_find_medication(mr, name, c);
  if(idx == -1) return;
  void (*destructor)(TElem) = (void (*) (TElem)) medication_destructor;
  vector_remove(mr->medication, idx, destructor);
}


void repository_updateMedicationQuantity(MedicationRepository* mr, char* name, double c, int q) {
  int idx = repository_find_medication(mr, name, c);
  if(idx == -1) return;
  ((Medication*)vector_get(mr->medication, idx))->quantity += q;
}


void repository_updateMedicationPrice(MedicationRepository* mr, char* name, double c, double p) {
  int idx = repository_find_medication(mr, name, c);
  if(idx == -1) return;
  printf("%f\n", ((Medication*)vector_get(mr->medication, idx))->price);
  ((Medication*)vector_get(mr->medication, idx))->price += p;
  printf("%f\n", ((Medication*)vector_get(mr->medication, idx))->price);
}


Vector* repository_getAll(MedicationRepository* mr) {
  return mr->medication;
}


void repository_destructor(MedicationRepository* mr) {
  void (*destructor)(TElem) = (void (*) (TElem)) medication_destructor;
  vector_destructor(mr->medication, destructor);
  free(mr);
}
