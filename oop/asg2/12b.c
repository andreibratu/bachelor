// Lab2 - Problem 12b

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Tuple {
  int sum;
  int length;
  int start;
};

int second(int* result)
{
    int size = 100;
    int idx = 0;
    int x;
    int* arr = (int*)malloc(sizeof(int)*size);

    printf("Please input numbers until EOF\n");

    while (scanf("%d", &x) != EOF) {
      if(idx == size) {
        arr = (int*)realloc(arr, sizeof(int)*size);
      }
      arr[idx++] = x;
    }

    assert(idx >= 1);

    // Start subseq from sum number
    struct Tuple ans;
    ans.sum = arr[0];
    ans.length = 0;
    ans.start = 0;
    struct Tuple current;
    current = ans;
    // Sequence we are looking for should only have positive numbers
    // Guard against sequence of only negative nubers
    int i=0;
    for(i=0; i<idx; i++) {
      int elem = arr[i];
      if(elem >= 0) {
        current.sum += elem;
        current.length += 1;
      }
      else {
        // Equal sum, longer length
        if (ans.sum == current.sum && ans.length < current.length) {
          ans = current;
        }
        // Larger sum
        else if(ans.sum < current.sum) {
          ans = current;
        }
        // Assume next number is not negative and start new subseq with it
        if(i+1<size) {
          current.sum = arr[i+1];
          current.length = 0;
          current.start = i+1;
        }
      }
    }

    if (ans.sum == current.sum && ans.length < current.length) {
      ans = current;
    }
    // Larger sum
    else if(ans.sum < current.sum) {
      ans = current;
    }
    result[0] = ans.sum;
    result[1] = ans.length;
    result[2] = ans.start;
    return 3;
}
