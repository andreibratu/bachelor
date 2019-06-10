#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>

class Player {
public:
  std::string name;
  std::string country;
  std::string team;
  int goals;

  Player();

  Player(std::string n, std::string c, std::string t, int g);

  Player(const Player& p);

};

std::ostream& operator << (std::ostream& s, const Player& p);

#endif
