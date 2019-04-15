#include <iostream>
#include <algorithm>
#include <functional>
#include "../controller/AdminController.h"
#include "AdminUI.h"
#include "../comparator/ComparatorMovieTitleAscending.h"

AdminUI::AdminUI(AdminController& c): cntrl{c} {}


void AdminUI::displayAll() {
  std::vector<Movie> all = this->cntrl.getAll();

  // ComparatorMovieTitleAscending comp = ComparatorMovieTitleAscending();
  // std::function<bool(const Movie&, const Movie&)> f = &(ComparatorMovieTitleAscending::compare);
  // std::sort(all.begin(), all.end(), f);

  for(int i = 0; i < (int)all.size(); i++) {
    std::cout << i << ". " << all[i] << '\n';
  }
}


void AdminUI::addMovie() {
  std::string name;
  std::string genre;
  std::string trailer;
  int year;

  std::cout << "Name: ";
  std::getline(std::cin, name);

  std::cout << "Genre: ";
  std::getline(std::cin, genre);

  std::cout << "Trailer: ";
  std::getline(std::cin, trailer);

  std::cout << "Year: ";
  std::cin >> year;

  this->cntrl.addMovie(name, genre, trailer, year);
}


void AdminUI::deleteMovie() {
  int idx;
  std::cout << "Index: ";
  std::cin >> idx;

  this->cntrl.deleteMovie(idx);
}


void AdminUI::newName() {
  int idx;
  std::string name;

  std::cout << "Index: ";
  std::cin >> idx;
  std::cin.ignore();

  std::cout << "New name: ";
  std::getline(std::cin, name);

  this->cntrl.updateName(idx, name);
}


void AdminUI::newGenre() {
  int idx;
  std::string genre;

  std::cout << "Index: ";
  std::cin >> idx;
  std::cin.ignore();

  std::cout << "New genre: ";
  std::getline(std::cin, genre);

  this->cntrl.updateGenre(idx, genre);
}


void AdminUI::newTrailer() {
  int idx;
  std::string trailer;

  std::cout << "Index: ";
  std::cin >> idx;
  std::cin.ignore();

  std::cout << "Trailer: ";
  std::getline(std::cin, trailer);

  this->cntrl.updateTrailer(idx, trailer);
}


void AdminUI::newYear() {
  int idx;
  int year;

  std::cout << "Index: ";
  std::cin >> idx;

  std::cout << "Year: ";
  std::cin >> year;

  this->cntrl.updateYear(idx, year);
}



void AdminUI::input_loop() {
  int option;
  bool flag = true;

while (flag) {
    std::cout << "Menu:\n\
1. List all\n\
2. Add movie\n\
3. Delete movie\n\
4. Update name\n\
5. Update genre\n\
6. Update trailer\n\
7. Update year\n\
8. Exit\n\
Your option: ";
    std::cin >> option;
    std::cin.ignore();
    try {
      switch(option) {
      case 1:
          system("clear");
          displayAll();
          break;
      case 2:
          addMovie();
          system("clear");
          break;
      case 3:
          deleteMovie();
          system("clear");
          break;
      case 4:
          newName();
          system("clear");
          break;
      case 5:
          newGenre();
          system("clear");
          break;
      case 6:
          newTrailer();
          system("clear");
          break;
      case 7:
          newYear();
          system("clear");
          break;
      case 8:
          flag = false;
          system("clear");
          break;
      }
    }
    catch(std::exception e) {
      std::cout << e.what() << '\n';
    }
  }
}
