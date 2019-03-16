#include "controller/MedicationController.h"
#include "ui/ui.h"
#include <stdlib.h>

int main() {
  MedicationController* mc = controller_init();
  char n1[] = "Asprina";
  char n2[] = "Aspacardin";
  char n3[] = "Modafinil";
  char n4[] = "Asperten";
  char n5[] = "Zizin";
  char n6[] = "Roziben";
  char n7[] = "Vadecin";
  char n8[] = "Sensatin";
  char n9[] = "Factive";
  char n10[] = "Tacrine";

  controller_addMedication(mc, n1, 5, 6, 7);
  controller_addMedication(mc, n2, 7, 3, 2);
  controller_addMedication(mc, n1, 6, 4, 9);
  controller_addMedication(mc, n3, 8, 4, 6);
  controller_addMedication(mc, n4, 7, 5, 3);
  controller_addMedication(mc, n5, 10, 8, 5);
  controller_addMedication(mc, n6, 9, 7, 8);
  controller_addMedication(mc, n7, 5, 8, 3);
  controller_addMedication(mc, n8, 7, 3, 6);
  controller_addMedication(mc, n9, 6, 4, 8);
  controller_addMedication(mc, n10, 7, 6, 7);
  input_loop(mc);
  free(mc);
  return 0;
}
