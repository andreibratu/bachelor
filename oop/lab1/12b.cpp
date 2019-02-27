// Lab2 - Problem 12b

#include <iostream>
#include <assert.h>
#include <vector>
#include <pair>

using namespace std;

int main()
{
    int x;
    vector<int> sequence;

    while (cin>>x) {
      sequence.push_back(x);
    }

    assert(sequence.size() >= 1);
    // Start subseq from first number
    pair<int, int> ans = make_pair(sequence[0], 1);
    pair<int, int> current = make_pair(sequence[0], 1);

    // Sequence we are looking for should only have positive numbers
    // Guard against sequence of only negative nubers
    for (int i=1, int& elem = sequence[i]; i<(int)sequence.size(); i++) {
      if(elem >= 0) {
        current.first += elem;
        current.second += 1;
      }
      else {
        // Equal sum, longer length
        if (ans.first == current.first && ans.second < current.second) {
          ans = current;
        }
        // Larger sum
        else if(ans.first < current.first) {
          ans = current;
        }
        // Assume next number is not negative and start new subseq with it
        current = make_pair(sequence[i+1], 1);
      }
    }
    return 0;
}
