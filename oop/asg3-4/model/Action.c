#include <stdlib.h>
#include <string.h>
#include "Action.h"

Action* action_init(int type, char* name, double concentration, int quantity, double price, double amount) {
  Action* a = (Action*)malloc(sizeof(Action));
  a->type = type;
  a->name = (char*)malloc(strlen(name)+1);
  strcpy(a->name, name);
  a->concentration = concentration;
  a->quantity = quantity;
  a->price = price;
  a->amount = amount;
  return a;
}

void action_destructor(Action* a) {
  free(a->name);
  free(a);
}
