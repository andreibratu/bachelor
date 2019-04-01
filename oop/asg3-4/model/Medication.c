#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Medication.h"


Medication* medication_init(char* name, double c, int q, double p) {
  Medication* m = (Medication*)malloc(sizeof(Medication));
  m->name = (char*)malloc(strlen(name)+1);
  strcpy(m->name, name);
  m->concentration = c;
  m->quantity = q;
  m->price = p;

  return m;
}


int medication_equal(const Medication* m1, const Medication* m2) {
  int name_cmp = strcmp(m1->name, m2->name);
  if(!name_cmp) {
    return m1->concentration == m2->concentration;
  }

  return 0;
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
  return sort_ascending(a, b) * -1;
}


Medication* copy_medication(Medication* m) {
  Medication* new_medication = (Medication*)malloc(sizeof(Medication));
  new_medication->name = (char*)malloc(strlen(m->name)+1);
  strcpy(new_medication->name, m->name);
  new_medication->concentration = m->concentration;
  new_medication->quantity = m->quantity;
  new_medication->price = m->price;

  return new_medication;
}


void medication_destructor(Medication* m) {
  assert(m);
  free(m->name);
  free(m);
}
