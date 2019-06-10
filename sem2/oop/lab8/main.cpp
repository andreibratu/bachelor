#include <iostream>
#include <vector>
#include "ComparatorAscendingString.h"
#include "ComparatorDescendingInteger.h"
#include "Sort.h"


template <class T>
void display(std::vector<T>& arr) {
  for(auto x:arr) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}



int main() {
  std::vector<int> v{1, 9, -4, 3, -1};
  ComparatorDescendingInteger c_integers = ComparatorDescendingInteger();
  sort(v, c_integers);
  display(v);

  std::vector<std::string> q{"cool", "asdf", "erty", "zvb"};
  ComparatorAscendingString c_strings = ComparatorAscendingString();
  sort(q, c_strings);
  display(q);

  return 0;
}
