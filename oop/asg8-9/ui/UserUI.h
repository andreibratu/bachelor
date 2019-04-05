#ifndef USER_UI_H
#define USER_UI_H
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

  void playTrailer();
public:
  UserUI(UserController& cntrl);

  void input_loop();
};

#endif
