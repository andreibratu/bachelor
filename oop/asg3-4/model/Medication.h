#ifndef MEDICATION_H
#define MEDICATION_H

typedef struct {
  char* name;
  double concentration;
  int quantity;
  double price;
} Medication;

// Constructor
Medication* medication_init(char*, double, int, double);

// Return 1 if equal in name and concentration else 0
int same(const Medication*, char*, double);

int sort_ascending(const void* a, const void* b);

int sort_descending(const void* a, const void* b);

void medication_destructor(Medication*);

#endif
