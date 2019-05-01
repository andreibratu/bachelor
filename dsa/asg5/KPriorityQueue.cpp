//
// Created by andreib on 22.04.2019.
//

#include <iostream>
#include "KPriorityQueue.h"
//theta(1)

KPriorityQueue::KPriorityQueue(Relation r, int k) {
	if (k <= 0) throw std::logic_error("Invalid k");

	this->k = k;

	this->r = Comp(r);
	this->reverse_r = Comp{ [r](TPriority p1, TPriority p2) {return !r(p1, p2); } };

	this->spares = Heap<Element>{ this->r };
	this->k_heap = Heap<Element>{ this->reverse_r };
}

//O(log n)
void KPriorityQueue::push(TElem e, TPriority p) {
	if (this->k_heap.size() < this->k) {
		this->k_heap.add({ e, p });
		return;
	}

	else if (this->k_heap.size() == this->k) {
		if (!this->r(this->k_heap.top().second, p)) {
			// New elem is better than any spare
			Element old_k_elem = this->k_heap.remove();
			this->k_heap.add({ e, p });
			this->spares.add(old_k_elem);
		}
		else {
			// It is not, moved directly to the spares
			this->spares.add({ e, p });
		}
	}


}

//theta(1)
Element KPriorityQueue::top() const {
	if (this->atMostKMinusOne()) throw std::logic_error("Not enough elements in heap");
	return this->k_heap.top();
}

//O(log n)
Element KPriorityQueue::pop() {
	if (this->k_heap.size() < this->k) {
		throw std::logic_error("Not enough elements!");
	}

	else {
		Element e = this->k_heap.remove();

		if (!this->spares.empty()) {
			Element new_k = this->spares.remove();
			this->k_heap.add(new_k);
		}

		return e;
	}
}

//theta(1)
bool KPriorityQueue::atMostKMinusOne() const {
	return this->k_heap.size() < this->k;
}

KPriorityQueue::~KPriorityQueue() {
};
