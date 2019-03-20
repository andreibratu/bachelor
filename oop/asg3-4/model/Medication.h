#ifndef MEDICATION_H
#define MEDICATION_H

typedef struct {
  // Model reperesentation of medication
  char* name;
  double concentration;
  int quantity;
  double price;
} Medication;

// Model constructor
Medication* medication_init(char*, double, int, double);

// Return 1 if Medication matches given name and concentration
int medication_equal(const Medication*, const Medication*);

// Sort ascending lexicographically or by concentration if equal
int sort_ascending(const void* a, const void* b);

// Sort after same criteria as ascending, only in reversed order
int sort_descending(const void* a, const void* b);

Medication* copy_medication(Medication*);

void medication_destructor(Medication*);

#endif
