#ifndef ACTION_H
#define ACTION_H

#define ADD 0
#define DELETE 1
#define UPDATEQ 2
#define UPDATEP 3


typedef struct {
  int type;
  char* name;
  double concentration;
  int quantity;
  double price;
  double amount;
} Action;


Action* action_init(int, char*, double, int, double, double);

void action_destructor(Action*);

#endif
