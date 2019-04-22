#ifndef USER_UI_H
#define USER_UI_H
#include "base/UserController.h"

class UserUI {
private:
  UserController& controller;

  void queryByGenre();

  void addToWatchlist();

  void nextMovie();

  void seeDetails();

  void removeWatchlist();

  void getWatchlist();

  void playTrailer();
public:
  UserUI(UserController& controller);

  void input_loop();
};

#endif
