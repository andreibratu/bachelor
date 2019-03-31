#include "../controller/UserController.h"

class UserUI {
private:
  UserController& c;

  void queryByGenre();

  void addToWatchlist();

  void nextMovie();

  void seeDetails();

  void removeWatchlist();

  void getWatchlist();
public:
  UserUI(UserController& cntrl);

  void input_loop();
};
