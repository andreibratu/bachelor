#include "MedicationVector.h"
#include "../model/Medication.h"
#include "stdlib.h"
#include <string.h>


MedicationVector* vector_init(int size) {
  MedicationVector* mv = (MedicationVector*)malloc(sizeof(MedicationVector));
  mv->medications = (Medication**)malloc(size*sizeof(Medication*));
  mv->capacity = size;
  mv->size = 0;
  return mv;
}


void vector_add(MedicationVector* mv, Medication* m) {
  if(mv->size == mv->capacity) {
    mv->capacity *= 2;
    mv->medications = (Medication**)realloc(
      mv->medications, sizeof(Medication*) * mv->capacity
    );
  }
  mv->medications[mv->size++] = m;
}


int vector_find(MedicationVector* mv, char* name, double concentration) {
  int i;
  for(i=0; i<mv->size; i++) {
    Medication* m = mv->medications[i];
    if(same(m, name, concentration)) return i;
  }

  return -1;
}


void vector_remove(MedicationVector* mv, char* name, double concentration) {
  int idx = vector_find(mv, name, concentration);
  if(idx == -1) return;
  Medication* will_be_freed = mv->medications[idx];
  memcpy(
    mv->medications+idx,
    mv->medications+idx+1,
    (mv->size-idx+1) * sizeof(Medication*)
  );
  mv->medications = (Medication**) realloc(mv->medications, sizeof(Medication*)*(mv->size-1));
  free(will_be_freed);
  mv->size -= 1;
}


void vector_destructor(MedicationVector* mv) {
  int i;
  for(i=0; i<mv->size; i++) {
    free(mv->medications[i]);
  }
  free(mv->medications);
  free(mv);
}
