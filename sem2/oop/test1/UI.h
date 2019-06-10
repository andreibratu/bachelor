#ifndef UI_H
#define UI_H
#include "Controller.h"

class UI {
private:
  Controller& controller;

  void addPlayer();

  void showAll();

  void goalsOfCountry();
public:
  UI(Controller& c);
  
  void loop();
};
#endif
