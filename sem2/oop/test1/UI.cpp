#include "UI.h"

UI::UI(Controller& c): controller{c} {}


void UI::addPlayer() {
  std::string n, c, t;
  int g;

  std::cout << "Name: ";
  std::cin >> n;
  std::cout << "Country: ";
  std::cin >> c;
  std::cout << "Team: ";
  std::cin >> t;
  std::cout << "Goals: ";
  std::cin >> g;

  if(!this->controller.addPlayer(n, c, t, g)) {
    std::cout << "\nPlayer already exists!\n\n";
  }
  else {
    std::cout << "\nPlayer added.\n\n";
  }
}


void UI::showAll() {
  std::vector<Player> all = this->controller.getAllSorted();

  for(auto x: all) {
    std::cout << x << '\n';
  }
  std::cout << '\n';
}


void UI::goalsOfCountry() {
  std::string c;
  std::cout << "Country: ";
  std::cin >> c;
  int result = this->controller.calculateScores(c);

  std::cout << result << '\n';
}


void UI::loop() {
  int flag = 1;
  while(flag) {
    std::cout << "1. Add\n2. Show all\n3. Goals by country\n4. Exit\n";
    int option;
    std::cin >> option;
    std::cin.ignore();
    switch (option) {
      case 1:
        this->addPlayer();
        break;
      case 2:
        this->showAll();
        break;
      case 3:
        this->goalsOfCountry();
        break;
      case 4:
        flag = 0;
        break;
    }
  }
}
