#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void get_digits(int x, int* digits) {
  int i;
  for(i=0; i<10; i++) digits[i] = 0;
  do {
    digits[x%10] = 1;
    x /= 10;
  } while(x!=0);
}

int compare_digits(int* arr1, int* arr2) {
  int i;
  for(i=0; i<10; i++) {
    if(arr1[i] != arr2[i]) {
      return 0;
    }
  }
  return 1;
}

int third(int* result) {
  int size = 100;
  int idx = 0;
  int x;
  int* arr = (int*)malloc(sizeof(int)*size);

  printf("Please input numbers while EOF\n");

  while (scanf("%d", &x) != EOF) {
    if(idx == size) {
      size *= 2;
      arr = (int*)realloc(arr, sizeof(int)*size);
    }
    arr[idx++] = x;
  }

  assert(idx >= 1);

  int digits_before[10] = {0};
  int digits_current[10] = {0};
  int curr_l=1, curr_start=0, best_l=1, best_start=0;

  get_digits(arr[0], digits_before);

  int i=1;
  for(i=1; i<idx; i++) {
    get_digits(arr[i], digits_current);
    if(compare_digits(digits_before, digits_current)) {
      curr_l += 1;
    }
    else {
      if(curr_l > best_l) {
        best_l = curr_l;
        best_start = curr_start;
        curr_l = 1;
        curr_start = i;
      }
    }
    get_digits(arr[i], digits_before);
  }
  result[0] = best_start;
  result[1] = best_l;
  return 2;
}
