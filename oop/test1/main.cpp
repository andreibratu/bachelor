#include "Repository.h"
#include "Controller.h"
#include "UI.h"


int main () {
  Repository p;
  p.addPlayer(Player{"Maria", "ROU", "CSM Wow", 15});
  p.addPlayer(Player{"Lori", "FRA", "Agrepine", 10});
  p.addPlayer(Player{"Elena", "ROU", "HC Baia Mare", 20});
  p.addPlayer(Player{"Shia", "ALG", "FCE Azerj", 30});
  p.addPlayer(Player{"Daiane", "FRA", "Agrepine", 17});
  Controller c{p};
  UI ui{c};

  ui.loop();
  return 0;
}
