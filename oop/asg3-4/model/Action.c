#include "Action.h"

Action* action_init(char* action, char* name, double concentration, int quantity, double price, double amount) {
  Action* a = (Action*)malloc(sizeof(Action));
  a->action = action;
  a->name = name;
  a->concentration = concentration;
  a->quantity = quantity;
  a->price = price;
  a->amount = amount;
  return a;
}
