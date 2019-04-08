#include "Player.h"


Player::Player() {}


Player::Player(std::string n, std::string c, std::string t, int g) {
  name = n;
  country = c;
  team = t;
  goals = g;
}


Player::Player(const Player& p) {
  name = p.name;
  country = p.country;
  team = p.team;
  goals = p.goals;
}


std::ostream& operator << (std::ostream& s, const Player& p) {
  s << p.name << " | " << p.country << " | " << p.team << " | " << p.goals;
  return s;
}
