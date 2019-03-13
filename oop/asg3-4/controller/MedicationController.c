#include <string.h>
#include "../model/Medication.h"
#include "../ds/MedicationVector.h"
#include "../repo/MedicationRepository.h"
#include "MedicationController.h"


MedicationController* controller_init() {
  MedicationController* mc = (MedicationController*)malloc(sizeof(MedicationController));
  MedicationRepository* mr = repository_init();
  mc->repo = mr;
  return mc;
}


MedicationVector* controller_shortSupply(MedicationController* mc, int x) {
  MedicationVector* ans = vector_init();
  MedicationVector* all = repository_getAll(mc->repo);

  int i;
  for(i=0; i<all->size; i++) {
    if(all->medications[i]->quantity < x) {
      vector_add(ans, all->medications[i]);
    }
  }

  return ans;
}


MedicationVector* controller_findByStr(MedicationController* mc, char* sstr) {
  MedicationVector* ans = vector_init();
  MedicationVector* all = repository_getAll(mc->repo);

  int i;
  for(i=0; i<all->size; i++) {
    if(strstr(all->medications[i]->name, sstr) != NULL) {
      vector_add(ans, all->medications[i]);
    }
  }

  return ans;
}


MedicationVector* controller_getAll(MedicationController* mc) {
  MedicationVector* all = repository_getAll(mc->repo);

  return all;
}


void controller_vector_repository_addMedication(MedicationController* mc, char* n, double c, int q, double p) {
  Medication* m = medication_init(n, c, q, p);
  repository_addMedication(mc->repo, m);
}


void controller_deleteMedication(MedicationController* mc, char* n, double c) {
  repository_deleteMedication(mc->repo, n, c);
}


void controller_updateMedicationQuantity(MedicationController* mc, char* n, double c, int nq) {
  repository_updateMedicationQuantity(mc->repo, n, c, nq);
}


void controller_updateMedicatonPrice(MedicationController* mc, char* n, double c, double np) {
  repository_updateMedicationPrice(mc->repo, n, c, np);
}

void controller_destructor(MedicationController* mc) {
  repository_destructor(mc->repo);
  free(mc);
}
