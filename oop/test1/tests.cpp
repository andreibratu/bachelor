#include <assert.h>
#include "Repository.h"
#include "Controller.h"
#include "Player.h"

int main () {
  Repository p;
  p.addPlayer(Player{"asdf", "ert", "qwe", 9});
  p.addPlayer(Player{"ertty", "ert", "rty", 6});
  Controller c{p};

  std::vector<Player> all = c.getAllSorted();
  assert(all.size() == 2);
  assert(all[0].goals == 9);

  assert(!p.addPlayer(Player{"asdf", "bla", "blabla", 5}));

  std::string wow = "ert";
  assert(c.calculateScores(wow) == 15);
  return 0;
}
