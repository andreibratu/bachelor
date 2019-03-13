#include <string.h>
#include "MedicationController.h"
#include "../ds/MedicationVector.h"


MedicationVector* shortSupply(MedicationController* mc, int x) {
  MedicationVector* ans = medication_vector_init(1);
  MedicationVector* all = getAll(mc->repo);

  int i;
  for(i=0; i<all->size; i++) {
    if(all->medications[i]->quantity < x) {
      add(ans, all->medications[i]);
    }
  }

  return ans;
}


MedicationVector* findByStr(MedicationController* mc, char* sstr) {
  MedicationVector* ans = medication_vector_init(1);
  MedicationVector* all = getAll(mc->repo);

  int i;
  for(i=0; i<all->size; i++) {
    if(strstr(all->medications[i]->name, sstr) != NULL) {
      add(ans, all->medications[i]);
    }
  }

  return ans;
}


MedicationVector* getAll(MedicationController* mc) {
  MedicationVector* all = getAll(mc->repo);

  return all;
}
