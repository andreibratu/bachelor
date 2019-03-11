#include "Medication.h"
#include <stdlib.h>
#include <string.h>

Medication* init(char* name, double c, int q, double p) {
  Medication* m = (Medication*)malloc(sizeof(Medication));
  m->name = name;
  m->concentration = c;
  m->quantity = q;
  m->price = p;

  return m;
}

int cmp(const Medication* m1, const Medication* m2) {
  int name_cmp = strcmp(m1->name, m1->name);
  if(!name_cmp) {
    if(m1->concentration < m2->concentration) return -1;
    if(m1->concentration == m2->concentration) return 0;
    return 1;
  }
  else return name_cmp;
}


int same(const Medication* m, char* name, double concentration) {
  int name_cmp = strcmp(m->name, name);
  if(!name_cmp) {
    return m->concentration == concentration;
  }

  return 0;
}

void destroy(Medication* m) {
  free(m);
}
