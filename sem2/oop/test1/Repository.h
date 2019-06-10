#ifndef REPO_H
#define REPO_H
#include <vector>
#include "Player.h"

class Repository {
private:
  std::vector<Player> players;
public:

  bool addPlayer(Player p);

  bool find(std::string& name);

  std::vector<Player> getAll();

  std::vector<Player> getByCountry(std::string& country);
};
#endif
