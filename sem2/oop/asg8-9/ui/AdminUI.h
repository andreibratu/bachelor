#ifndef ADMIN_UI_H
#define ADMIN_UI_H

#include "base/AdminController.h"


class AdminUI {
private:
  AdminController& controller;

  void addMovie();

  void deleteMovie();

  void newName();

  void newGenre();

  void newTrailer();

  void newYear();

  void displayAll();

  void show();
public:
  explicit AdminUI(AdminController& controller);

  void input_loop();
};


#endif
