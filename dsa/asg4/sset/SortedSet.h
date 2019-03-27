#ifndef SSET_H
#define SSET_H

#include "../lla/LinkedListArray.h"
#include "../iter/LLAIterator.h"

typedef int TElem;
typedef TElem TComp;

typedef bool(*Relation)(TComp, TComp);
typedef LLAIterator<int> SortedSetIterator;

class SortedSet {
private:
	Relation r;
	LLA<int> items;
public:
	//constructor
	SortedSet(Relation r);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set)
	//it returns false
	bool add(TComp e);


	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;


	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();


};


#endif
