#ifndef K_PRIOR_Q
#define K_PRIOR_Q

#include <utility>
#include "Heap.h"

using namespace std;

typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);


class KPriorityQueue {

private:
    int k;
	Heap<Element> spares;
	Heap<Element> k_heap;
	Comp r;
	Comp reverse_r;
	//representation of the K PriorityQueue

public:

	//throws an exception if k is less than or equal to 0
	KPriorityQueue(Relation r, int k);

	//adds an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the kth highest priority with respect to the order relation
	//throws exception if the queue has less than k elements
	Element top()  const;


	//removes and returns the element with the kth highest priority
	//throws exception if the queue has less than k elements
	Element pop();

	//checks if the queue has less than k elements
	bool atMostKMinusOne() const;

	//destructor
	~KPriorityQueue();
};

#endif
