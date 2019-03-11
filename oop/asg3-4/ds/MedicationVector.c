#include "MedicationVector.h"
#include "../model/Medication.h"
#include "stdlib.h"
#include <cstring>

MedicationVector* init(int size) {
  MedicationVector* mv = (MedicationVector*)malloc(sizeof(MedicationVector));
  mv->medications = (Medication*)malloc(size*sizeof(Medication));
  mv->capacity = size;
  mv->size = 0;
  return mv;
}

void add(MedicationVector* mv, Medication m) {
  if(mv->size == mv->capacity) {
    mv->capacity *= 2;
    mv->medications = (Medication*)realloc(
      mv->medications, sizeof(Medication) * mv->capacity
    );
  }
  mv->medications[mv->size++] = m;
}

int find(MedicationVector* mv, char* name, double concentration) {
  int i;
  for(i=0; i<mv->size; i++) {
    Medication* m = &mv->medications[i];
    if(same(m, name, concentration)) return i;
  }

  return -1;
}
