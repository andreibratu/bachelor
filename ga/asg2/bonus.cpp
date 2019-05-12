/*
Wolf, goat and cabbage problem:
A man has a wolf, a goat and a cabbage must cross a river
in a boat than can hold him and only one of the three items.
He cannot leave alone the wolf with the goat or the goat
with the cabbage. Find a shortest sequence of moves for crossing the river.
*/

#include <iostream>
#include <unordered_set>
#include <queue>
#include "BFS.h"

#define START_STATE 240
#define END_STATE 15

bool was_seen(std::unordered_set<int>& memo, int& bitmask) {
  return memo.find(bitmask) != memo.end();
}


bool valid(int& bitmask) {
  bool man_on_left = bitmask & (1<<7);
  if(man_on_left) {
    if((bitmask & (1<<1)) && (bitmask & (1<<0))) return false;

    if((bitmask & (1<<2)) && (bitmask & (1<<1))) return false;
  }
  else {
    if((bitmask & (1<<6)) && (bitmask & (1<<5))) return false;

    if((bitmask & (1<<5)) && (bitmask & (1<<4))) return false;
  }

  return true;
}


bool is_final(int& bitmask) {
    return bitmask == END_STATE;
}


void get_neighbours(Graph& g, std::queue<int>& q, int cNode) {
  // Left bank
  if((cNode & (1<<7))) {
    int move_guy_right = ((cNode ^ (1<<7)) | (1<<3));
    q.push(move_guy_right);

    std::cout << move_guy_right << '\n';

    g.add_edge(cNode, move_guy_right);
    g.add_edge(move_guy_right, cNode);

    for(int i = 6; i >= 4; i--) {
      if(cNode & (1<<i)) {
        int move_right = ((cNode ^ (1<<i)) | (1<<(i-4)));
        move_right = ((move_right ^ (1<<7)) | (1<<3)); // Also take the guy
        q.push(move_right);

        g.add_vertex(move_right);
        g.add_edge(cNode, move_right);
        g.add_edge(move_right, cNode);

        std::cout << move_right << '\n';
      }
    }
  }
  else {
    int move_guy_left = ((cNode ^ (1<<3)) | (1<<7));
    q.push(move_guy_left);

    std::cout << move_guy_left << '\n';

    g.add_edge(cNode, move_guy_left);
    g.add_edge(move_guy_left, cNode);

    for(int i = 0; i < 3; i++) {
      if(cNode & (1<<i)) {
        int move_left = (cNode ^ (1<<i)) | (1<<(i+4));
        move_left = (move_left ^ (1<<3)) | (1<<7); // Also take the guy
        q.push(move_left);

        g.add_vertex(move_left);
        g.add_edge(cNode, move_left);
        g.add_edge(move_left, cNode);

        std::cout << move_left << '\n';
      }
    }
  }
}


int main() {
  Graph g;
  g.add_vertex(START_STATE);
  std::unordered_set<int> seen;
  std::queue<int> q;
  q.push(START_STATE);
  while(true) {
    int state = q.front();
    std::cout << "--------\nCurrent: " << state << '\n';
    q.pop();
    if(is_final(state)) {
      std::cout << "Found it!\n";
      break;
    }
    if(!valid(state) || was_seen(seen, state)) continue;

    get_neighbours(g, q, state);
    seen.insert(state);
  }

  return 0;
}
