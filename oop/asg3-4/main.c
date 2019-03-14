#include "controller/MedicationController.h"
#include "ui/ui.h"
#include <stdlib.h>

int main() {
  MedicationController* mc = controller_init();
  input_loop(mc);
  free(mc);
  return 0;
}
