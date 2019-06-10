#include "Controller.h"
#include <algorithm>

Controller::Controller(Repository& r): repo{r} {}


bool Controller::addPlayer(std::string& n, std::string& c, std::string& t, int g) {
  return this->repo.addPlayer(Player{n, c, t, g});
}


std::vector<Player> Controller::getAllSorted() {
  std::vector<Player> all = this->repo.getAll();
  std::sort(
    all.begin(),
    all.end(),
    [](const Player& p1, const Player& p2) {return p1.goals > p2.goals;}
  );

  return all;
}


int Controller::calculateScores(std::string& c) {
  std::vector<Player> byCountry = this->repo.getByCountry(c);

  int sum = 0;
  for(auto x: byCountry) {
    sum += x.goals;
  }

  return sum;
}
