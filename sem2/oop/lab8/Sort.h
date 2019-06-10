#ifndef MY_SORT_H
#define MY_SORT_H

#include <vector>
#include "Comparator.h"

template <class T>
void sort(std::vector<T>& arr, Comparator<T>& c) {
  int s = arr.size();
  for(int i = 0; i < s; i++) {
    for(int j = i+1; j < s; j++) {
      if(c.compare(arr[i], arr[j])) {
        std::swap(arr[i], arr[j]);
      }
    }
  }
}

#endif
