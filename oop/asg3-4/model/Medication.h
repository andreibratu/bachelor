#ifndef MEDICATION_H
#define MEDICATION_H

typedef struct {
  char* name;
  double concentration;
  int quantity;
  double price;
} Medication;

// Constructor
Medication* init(char*, double, int, double);

int cmp(const Medication*, const Medication*);

// Return 1 if equal in name and concentration else 0
int same(const Medication*, char*, double);

void destroy(Medication*);

#endif
