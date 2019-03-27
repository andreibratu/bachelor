#ifndef DLL_H
#define DLL_H

#include "../Node.h"
#include "../iter/DLLIterator.h"

template <class U> class DLLIterator;

template <class T>
class DLL {

private:
  Node<T>* head;
  Node<T>* curr;
  int size;
  template <typename U> friend class DLLIterator;
public:

  // Constructor
  DLL() {
    this->head = new Node<T>;
    this->curr = head;
  }


  // Insert new val before given Node
  // If NULL is given as param, add element at the end
  void insert(Node<T>* n, T val) {
    if(n == 0) {
      this->curr->val = val;
      this->curr->next = new Node<T>;
      this->curr->next->before = this->curr;
      this->curr = this->curr->next;
    }

    else {
      Node<T>* before = n->before;
      n->before = new Node<T>;
      n->before->val = val;
      n->before->next = n;
      before->next = n->before;
      n->before->before = before;
    }

    this->size += 1;
  }


  // Update value in given node
  // Node pointers can be obtained via DLLIterator
  // O(1) due to pointer reference
  void update(Node<T>* n, T val) {
    n->val = val;
  }


  // Obtain the value held in a node
  // O(1) due to pointer reference
  T get(Node<T>* n) const {
    return n->val;
  }


  // Obtain the size of the DLL
  // O(1)
  int getSize() const {
    return this->size;
  }


  // Obtain iterator pointing at the start of the list
  // O(1)
  DLLIterator<T> getIterator() const {
    return DLLIterator<T>(*this);
  }

  // Destructor
  // O(n), all nodes must be freed
  ~DLL() {
    Node<T>* it = this->head;
    Node<T>* next = this->head->next;
    while(it != 0) {
      delete it;
      it = next;
      if(it != 0) next = it->next;
    }
  }
};

#endif
