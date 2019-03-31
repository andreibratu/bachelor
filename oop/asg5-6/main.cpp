#include "ds/Vector.h"
#include "repo/Repository.h"
#include "controller/AdminController.h"
#include "controller/UserController.h"
#include "ui/AdminUI.h"
#include "ui/UserUI.h"


int main() {
  Repository r;
  r.addMovie(Movie{"Pulp Fiction", "Thriller", "https://youtu.be/s7EdQ4FqbhY", 1994});
  r.addMovie(Movie{"The Godfather", "Crime", "https://youtu.be/sY1S34973zA", 1974});
  r.addMovie(Movie{"Schindler's List", "Biography", "https://youtu.be/gG22XNhtnoY", 1993});
  r.addMovie(Movie{"Citizen Kane", "Mystery", "https://youtu.be/8dxh3lwdOFw", 1941});
  r.addMovie(Movie{"The Shawshank Redemption", "Drama", "https://youtu.be/6hB3S9bIaco", 1994});
  r.addMovie(Movie{"Casablanca", "Drama", "https://youtu.be/BkL9l7qovsE", 1942});
  r.addMovie(Movie{"One Flew Over the Cuckoo's Nest", "Drama", "https://youtu.be/OXrcDonY-B8", 1975});

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
