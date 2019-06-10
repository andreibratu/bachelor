#include <stdio.h>
#include "repo/MedicationRepository.h"
#include "controller/MedicationController.h"
// #include "controller/list/MedicationListController.h"
#include "history/HistoryController.h"
// #include "history/list/HistoryListController.h"
#include "ui/UI.h"
// #include "ui/list/UIList.h"


int main() {
  char n1[] = "Aspirina";
  char n2[] = "Aspacardin";
  char n3[] = "Modafinil";
  char n4[] = "Asperten";
  char n5[] = "Zizin";
  char n6[] = "Roziben";
  char n7[] = "Vadecin";
  char n8[] = "Sensatin";
  char n9[] = "Factive";
  char n10[] = "Tacrine";


    HistoryController* hc = history_controller_init();
    MedicationController* mc = controller_init();

    mc->history = hc;

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
    controller_destructor(mc);
  // int option = -1;
  // while(option != 0 || option != 1) {
  //   printf("Unit undo (0) / List undo (1) ? ");
  //   scanf("%d", &option);
  // }
  //
  // if(option) {
  //   HistoryListController* hc = history_list_controller_init();
  //   MedicationListController* mc = list_controller_init(hc);
  //
  //   list_controller_addMedication(mc, n1, 5, 6, 7);
  //   list_controller_addMedication(mc, n2, 7, 3, 2);
  //   list_controller_addMedication(mc, n1, 6, 4, 9);
  //   list_controller_addMedication(mc, n3, 8, 4, 6);
  //   list_controller_addMedication(mc, n4, 7, 5, 3);
  //   list_controller_addMedication(mc, n5, 10, 8, 5);
  //   list_controller_addMedication(mc, n6, 9, 7, 8);
  //   list_controller_addMedication(mc, n7, 5, 8, 3);
  //   list_controller_addMedication(mc, n8, 7, 3, 6);
  //   list_controller_addMedication(mc, n9, 6, 4, 8);
  //   list_controller_addMedication(mc, n10, 7, 6, 7);
  //
  //   list_input_loop(mc);
  //   list_controller_destructor(mc);
  // }
  // else {
  //   HistoryController* hc = history_controller_init();
  //   MedicationController* mc = controller_init(hc);
  //
  //   controller_addMedication(mc, n1, 5, 6, 7);
  //   controller_addMedication(mc, n2, 7, 3, 2);
  //   controller_addMedication(mc, n1, 6, 4, 9);
  //   controller_addMedication(mc, n3, 8, 4, 6);
  //   controller_addMedication(mc, n4, 7, 5, 3);
  //   controller_addMedication(mc, n5, 10, 8, 5);
  //   controller_addMedication(mc, n6, 9, 7, 8);
  //   controller_addMedication(mc, n7, 5, 8, 3);
  //   controller_addMedication(mc, n8, 7, 3, 6);
  //   controller_addMedication(mc, n9, 6, 4, 8);
  //   controller_addMedication(mc, n10, 7, 6, 7);
  //
  //   input_loop(mc);
  //   controller_destructor(mc);
  // }

  return 0;
}
