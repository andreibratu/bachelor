#include <stdlib.h>
#include <string.h>
#include "Medication.h"

Medication* medication_init(char* name, double c, int q, double p) {
  Medication* m = (Medication*)malloc(sizeof(Medication));
  m->name = name;
  m->concentration = c;
  m->quantity = q;
  m->price = p;

  return m;
}


int sort_ascending(const void* a, const void* b) {
  Medication* m1 = (Medication*)a;
  Medication* m2 = (Medication*)b;
  if(strcmp(m1->name, m2->name) == 0) {
    double p = m1->concentration-m2->concentration;
    if(p<0) return -1;
    if(p>0) return 1;
    return 0;
  }
  int c = strcmp(m1->name, m2->name);
  if(c < 0) return -1;
  return 1;
}


int sort_descending(const void* a, const void* b) {
  Medication* m1 = (Medication*)a;
  Medication* m2 = (Medication*)b;
  if(strcmp(m2->name, m1->name) == 0) {
    double p = m1->concentration-m2->concentration;
    if(p<0) return 1;
    if(p>0) return -1;
    return 0;
  }
  int c = strcmp(m1->name, m2->name);
  if(c < 0) return 1;
  return -1;
}


int same(const Medication* m, char* name, double concentration) {
  int name_cmp = strcmp(m->name, name);
  if(!name_cmp) {
    return m->concentration == concentration;
  }

  return 0;
}


void medication_destructor(Medication* m) {
  free(m);
}
