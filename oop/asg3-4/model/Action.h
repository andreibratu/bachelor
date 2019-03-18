typedef struct {
  char* action;
  char* name;
  double concentration;
  int quantity;
  double price;
  double amount;
} Action;


Action* action_init(char* action, char* name, double concentration, int quantity, double price, double amount);

void medication_destructor(Action*);
