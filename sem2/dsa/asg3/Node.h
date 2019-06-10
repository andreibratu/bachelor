#ifndef NODE_H
#define NODE_H

template <class T>
struct Node {
  T val;
  Node* before;
  Node* next;

  Node() {
    this->before = 0;
    this->next = 0;
  }
};

#endif
