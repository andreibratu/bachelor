#include "controller/MedicationController.h"
#include "ui/ui.h"

int main() {
  MedicationController* mc = controller_init();
  input_loop(mc);
  return 0;
}
