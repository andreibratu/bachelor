#include "controller/AdminController.h"
#include "ds/Vector.h"
#include "repo/Repository.h"
#include "ui/AdminUI.h"


int main() {
  Vector<Movie> v{};
  Repository r{v};
  AdminController c{r};
  input_loop(c);
  return 0;
}
