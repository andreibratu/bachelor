#include "UserUI.h"
#include <sstream>


UserUI::UserUI(UserController& cntrl): c{cntrl} {}


void UserUI::queryByGenre() {
  std::string query;
  std::cout << "Input query: ";
  std::getline(std::cin, query);
  Vector<Movie> ans = this->c.queryByGenre(query);

  int option;
  bool input_flag = 1;

  system("clear");

  while(input_flag) {
    std::cout << ans << '\n';
    std::cout << "Menu:\n\
1. See details\n\
2. Next movie\n\
3. Add to watchlist\n\
4. Exit\n\
Your option: ";
    std::cin >> option;
    std::cin.ignore();
    switch (option) {
      case 1:
        system("clear");
        this->seeDetails();
        break;
      case 2:
        this->nextMovie();
        system("clear");
        break;
      case 3:
        this->addToWatchlist();
        break;
      case 4:
        input_flag = 0;
        break;
    }
  }
}


void UserUI::addToWatchlist() {
  this->c.addToWatchList();
}


void UserUI::nextMovie() {
  this->c.nextMovie();
}


void UserUI::seeDetails() {
  Movie m = this->c.seeDetails();
  std::stringstream ss;
  ss << "google-chrome " << m.getTrailer();
  system(ss.str().c_str());
  system("clear");
  std::cout << m << "\n\n";
}


void UserUI::getWatchlist() {
  Vector<Movie> wl = this->c.getWatchlist();

  if(wl.size()) {
    std::cout << wl;
  }
  else {
    std::cout << "Watchlist is empty!\n";
  }
}


void UserUI::removeWatchlist() {
  if(!this->c.getWatchlist().size()) {
    system("clear");
    std::cout << "Watchlist is empty!\n";
    return;
  }

  int idx;
  int liked;

  std::cout << "Index: ";
  std::cin >> idx;
  std::cout << "Did you like it (0/1) ? ";
  std::cin >> liked;

  std::cout << "GOT HERE\n";
  try {
    this->c.removeWatchlist(idx, liked);
    system("clear");
  }
  catch(std::exception e) {
    std::cout << "Invalid input!\n";
  }
}


void UserUI::input_loop() {
  bool input_flag = 1;
  int option;

  while(input_flag) {
    std::cout << "Menu:\n\
1. Query by genre\n\
2. See watchlist\n\
3. Remove movie from watchlist\n\
4. Exit\n\
Your option: ";
    std::cin >> option;
    std::cin.ignore();
    switch (option) {
      case 1:
        this->queryByGenre();
        break;
      case 2:
        system("clear");
        this->getWatchlist();
        break;
      case 3:
        this->removeWatchlist();
        break;
      case 4:
        input_flag = 0;
        system("clear");
        break;
    }
  }
}
