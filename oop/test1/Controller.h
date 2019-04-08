#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Repository.h"

class Controller {
private:
  Repository& repo;
public:
  Controller(Repository& r);

  /*
  Add new player to db.

  Args:
    n (std::string&) Name of the player
    c (std::string&) Country of the player
    t (std::string&) Team of the player
    g (int) Goals scored by player
  Returns:
    True if no player with given name existed, and creation was succesful
  */
  bool addPlayer(std::string& n, std::string& c, std::string& t, int goals);

  std::vector<Player> getAllSorted();

  /*
  Calculate goals scored by all players from given country.

  Args:
    c (std::string&) Country of origin
  Returns:
    An integer representing how mnay goals were scored.
  */
  int calculateScores(std::string& c);
};
#endif
