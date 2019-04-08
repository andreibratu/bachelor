#include "Repository.h"
#include <algorithm>

bool Repository::addPlayer(Player p) {
  if(this->find(p.name)) return false;

  this->players.push_back(p);
  return true;
}


bool Repository::find(std::string& name) {
  return std::find_if(
    this->players.begin(),
    this->players.end(),
    [name](const Player& p) {return p.name == name;}
  ) != this->players.end();
}


std::vector<Player> Repository::getAll() {
  return std::vector<Player>(this->players);
}


std::vector<Player> Repository::getByCountry(std::string& country) {
  std::vector<Player> ans(this->players.size());

  auto it = std::copy_if(
    this->players.begin(),
    this->players.end(),
    ans.begin(),
    [country](const Player& p) {return p.country == country;}
  );

  ans.resize(std::distance(ans.begin(), it));
  return ans;
}
