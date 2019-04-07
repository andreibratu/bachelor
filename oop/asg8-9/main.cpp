#include "repo/Repository.h"
#include "controller/AdminController.h"
#include "controller/UserController.h"
#include "ui/AdminUI.h"
#include "ui/UserUI.h"


int main() {
  Repository r;

  int option = -1;
  while(option < 0 || option > 1) {
    std::cout << "Admin(0) / User(1)? ";
    std::cin >> option;
  }

  std::cin.ignore();

  if(!option) {
    AdminController c{r};
    AdminUI ui{c};
    ui.input_loop();
  }
  else {
    UserController c{r};
    UserUI ui{c};
    ui.input_loop();
  }

  return 0;
}
