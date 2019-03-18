#include <stdio.h>
#include "../controller/MedicationController.h"
#include "../ds/Vector.h"
#include "../model/Medication.h"


void display_vector(vector* v) {
  if(v->size == 0)
    printf("Nothing to display!\n\n");
  else {
    int i;
    for(i=0; i<v->size; i++) {
      Medication* m = (Medication*)vector_get(v, i);
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
  int quantity_bound;
  double price_bound;
  int option;
  int sorting = -1;

  while (flag) {
    sorting = -1;
    printf("%s", "\n\nChoose an option:\n\
1. List all medication\n\
2. Add medication\n\
3. Delete medication\n\
4. Update price\n\
5. Update quantity\n\
6. Filter by supply quantity\n\
7. Filter by price\n\
8. List by partial search on name\n\
9. Exit\n");
     printf("%s: ", "Your option");
     scanf("%d", &option);
     printf("\n\n");
     if(option == 1) {
       mv = controller_getAll(mc);
       display_vector(mv);
       continue;
     }
     if(option == 2) {
       printf("%s: ", "Enter name");
       scanf("%s", name);
       printf("%s: ", "Enter concentration");
       scanf("%lf", &concentration);
       printf("%s: ", "Enter quantity");
       scanf("%d", &quantity);
       printf("%s: ", "Enter price");
       scanf("%lf", &price);
       controller_addMedication(mc, name, concentration, quantity, price);
       continue;
     }
     if(option == 3) {
       printf("%s: ", "Enter name");
       scanf("%s", name);
       printf("%s: ", "Enter concentration");
       scanf("%lf", &concentration);
       controller_deleteMedication(mc, name, concentration);
       continue;
     }
     if(option == 4) {
       printf("%s: ", "Enter name");
       scanf("%s", name);
       printf("%s: ", "Enter concentration");
       scanf("%lf", &concentration);
       printf("%s: ", "Enter price modification");
       scanf("%lf", &price);
       controller_updateMedicatonPrice(mc, name, concentration, price);
       continue;
     }
     if(option == 5) {
       printf("%s: ", "Enter name");
       scanf("%s", name);
       printf("%s: ", "Enter concentration");
       scanf("%lf", &concentration);
       printf("%s: ", "Enter quantity modification");
       scanf("%d", &quantity);
       controller_updateMedicationQuantity(mc, name, concentration, quantity);
       continue;
     }
     if(option == 6) {
       printf("%s: ", "Enter quantity upper bound");
       scanf("%d", &quantity_bound);
       mv = controller_shortSupply(mc, quantity_bound);
       display_vector(mv);
       continue;
     }
     if(option == 7) {
       printf("%s", "Enter price lower bound: ");
       scanf("%lf", &price_bound);
       mv = controller_highPrice(mc, price_bound);
       display_vector(mv);
       continue;
     }
     if(option == 8) {
       printf("%s: ", "Enter a substring");
       scanf("%s", ss);
       while(sorting == -1) {
         printf("Sort ascending (1) / descending (0)? ");
         scanf("%d", &sorting);
         printf("\n");
         if(sorting < 0 || sorting > 1) {
           sorting = -1;
         }
       }
       mv = controller_findByStr(mc, ss, sorting);
       display_vector(mv);
       continue;
     }
     if(option == 9) {
       flag = 0;
       continue;
     }
   }
}
