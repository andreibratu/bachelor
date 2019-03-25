#include <iostream>
#include "../controller/AdminController.h"


void display_vector(Vector<Movie>& v) {
  for(int i=0; i<v.size(); i++) {
    std::cout << i <<". - " << v[i].getName() << '-' << v[i].getGenre() << '-' << v[i].getTrailer() << '-' << v[i].getYear() << '-' << v[i].getLikes() << '\n';
  }
}


void input_loop(AdminController& c) {
  int option;
  std::string name;
  std::string genre;
  std::string trailer;
  int year;
  int idx;
  bool result;
  bool flag = true;
  Vector<Movie> v{};

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
    std::cout << '\n';
    switch(option) {
    case 1:
        v = c.getAll();
        display_vector(v);
        break;
    case 2:
        std::cout << "Name: ";
        std::cin >> name;
        std::cout << '\n';

        std::cout << "Genre: ";
        std::cin >> genre;
        std::cout << '\n';

        std::cout << "Trailer: ";
        std::cin >> trailer;
        std::cout << '\n';

        std::cout << "Year: ";
        std::cin >> year;
        std::cout << '\n';

        c.addMovie(name, genre, trailer, year);
        break;
    case 3:
        std::cout << "Index: ";
        std::cin >> idx;

        result = c.deleteMovie(idx);
        if(!result) std::cout << "Invalid index!\n";
        break;
    case 4:
        std::cout << "Index:\n";
        std::cin >> idx;

        std::cout << "New name:\n";
        std::cin >> genre;

        result = c.updateName(idx, name);
        if(!result) std::cout << "Invalid index!\n";
        break;
    case 5:
        std::cout << "Index: ";
        std::cin >> idx;

        std::cout << "New genre: ";
        std::cin >> genre;

        result = c.updateGenre(idx, genre);
        if(!result) std::cout << "Invalid index!\n";
        break;
    case 6:
      std::cout << "Index: ";
      std::cin >> idx;

      std::cout << "Trailer: ";
      std::cin >> trailer;

      result = c.updateTrailer(idx, trailer);
      if(!result) std::cout << "Invalid index!\n";
      break;
    case 7:
      std::cout << "Index: ";
      std::cin >> idx;

      std::cout << "Year: ";
      std::cin >> year;

      result = c.updateYear(idx, year);
      if(!result) std::cout << "Invalid index!\n";
      break;
    case 8:
      flag = false;
      break;
    }
  }
}
