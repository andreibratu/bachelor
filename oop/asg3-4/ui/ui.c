#include <stdio.h>
#include "../controller/MedicationController.h"
#include "../model/Medication.h"


void display_vector(MedicationVector* mv) {
  if(mv->size == 0)
    printf("Noting to display!\n\n");
  else {
    int i;
    for(i=0; i<mv->size; i++) {
      Medication* m = mv->medications[i];
      printf("%s %f %d %f\n", m->name, m->concentration, m->quantity, m->price);
    }
  }
}


void input_loop(MedicationController* mc) {
  int flag = 1;
  MedicationVector* mv;
  char* name = (char*)malloc(100);
  char* ss = (char*)malloc(100);
  double concentration;
  int quantity;
  double price;
  int low_quantity;

  while (flag) {
    printf("%s", "Choose an option:\n\
1. List all medication\n\
2. Add medication\n\
3. Delete medication\n\
4. Update price\n\
5. Update quantity\n\
6. List short supply\n\
7. List by partial search on name\n\
8. Exit\n");
     printf("%s: ", "Your option");
     int option = getchar() - '0';

     switch (option) {
       case 1:
         mv = controller_getAll(mc);
         display_vector(mv);
         break;
       case 2:
         printf("%s: ", "Enter name");
         scanf("%s", name);
         printf("%s: ", "Enter concentration");
         scanf("%lf", &concentration);
         printf("%s: ", "Enter quantity");
         scanf("%d", &quantity);
         printf("%s: ", "Enter price");
         scanf("%lf", &price);
         controller_addMedication(mc, name, concentration, quantity, price);
         break;
       case 3:
         printf("%s: ", "Enter name");
         scanf("%s", name);
         printf("%s: ", "Enter concentration");
         scanf("%lf", &concentration);
         controller_deleteMedication(mc, name, concentration);
         break;
       case 4:
         printf("%s: ", "Enter name");
         scanf("%s", name);
         printf("%s: ", "Enter concentration");
         scanf("%lf", &concentration);
         printf("%s: ", "Enter price modification");
         scanf("%lf", &price);
         controller_updateMedicatonPrice(mc, name, concentration, price);
         break;
       case 5:
         printf("%s: ", "Enter name");
         scanf("%s", name);
         printf("%s: ", "Enter concentration");
         scanf("%lf", &concentration);
         printf("%s: ", "Enter quantity modification");
         scanf("%d", &quantity);
         controller_updateMedicationQuantity(mc, name, concentration, quantity);
         break;
       case 6:
         printf("%s: ", "Enter quantity lower bound");
         scanf("%d", &low_quantity);
         mv = controller_shortSupply(mc, low_quantity);
         display_vector(mv);
         break;
       case 7:
         printf("%s: ", "Enter a substring");
         scanf("%s", ss);
         mv = controller_findByStr(mc, ss);
         display_vector(mv);
         break;
       case 8:
         flag = 0;
         break;
     }
     printf("\n\n");
   }
}
