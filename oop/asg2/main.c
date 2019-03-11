#include <stdio.h>
#include <stdlib.h>
#include "12a.h"
#include "12b.h"
#include "13b.h"

int main() {
  printf("Hello there!\nPlease choose an option:\n1. 12a\n2. 12b\n3. 13b\n");
  int ok=0;
  int option;
  while(!ok) {
    scanf("%d", &option);
    if(option >= 1 && option <= 3) {
      ok=1;
    }
  }
  int* result;
  int l, i;
  if(option == 1) {
    result = (int*)malloc(sizeof(int)*100);
    l = first(result);
  } else if(option == 2) {
    result = (int*)malloc(sizeof(int)*3);
    l = second(result);
  } else {
    result = (int*)malloc(sizeof(int)*2);
    l = third(result);
  }
  for(i=0; i<l; i++) printf("%d ", result[i]);
  printf("\n");
  return 0;
}
