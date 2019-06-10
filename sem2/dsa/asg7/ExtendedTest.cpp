#include <exception>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include "ExtendedTest.h"

using namespace std;

bool asc(TKey c1, TKey c2) {
	if (c1 <= c2) {
		return true;
	} else {
		return false;
	}
}

bool desc(TKey c1, TKey c2) {
	if (c1 >= c2) {
		return true;
	} else {
		return false;
	}
}

void testCreate() {
	SortedMultiMap smm = SortedMultiMap(asc);
	assert(smm.size() == 0);
	assert(smm.isEmpty());

	for (int i = 0; i < 10; i++) {
        vector<TValue> v= smm.search(i);
        assert(v.size()==0);
	}

	for (int i = -10; i < 10; i++) {
		vector<TValue> v= smm.search(i);
        assert(v.size()==0);
	}
}

void testSearch(Relation r) {
	SortedMultiMap smm = SortedMultiMap(r);
	int kMin = 0;
	int kMax = 10;
	for (int i = kMin; i <= kMax; i++) {
			smm.add(i, i + 1);
			smm.add(i, i + 2);
	}
	int intervalDim = 10;
	for (int i = kMin; i <= kMax; i++) {
        vector<TValue> v= smm.search(i);
        assert(v.size()==2);
	}
	for (int i = kMin - intervalDim; i < kMin; i++) {
        vector<TValue> v= smm.search(i);
        assert(v.size()==0);
	}
	for (int i = kMax + 1; i < kMax + intervalDim; i++) {
        vector<TValue> v= smm.search(i);
        assert(v.size()==0);
	}
}

void testSearch() {
	testSearch(asc);
	testSearch(desc);
}

void populateSMMEmpty(SortedMultiMap& smm, int min, int max) {
	for (int i = min; i <= max; i++) {
        smm.add(i, i);
		if (i%2 ==0)
            smm.add(i, i+2);
	}
}

void testRemoveSearch(Relation r) {
	SortedMultiMap smm = SortedMultiMap(r);
	int min = 10;
	int max = 20;
	populateSMMEmpty(smm, min, max);
	for (int c = min; c <= max; c++) {
		assert(smm.remove(c, c+1) == false);
		if (c%2==0)
            assert(smm.remove(c,c) == true);
	}
	
	for (int c = min; c <= max; c++) {
		if (c%2==1){
            assert(smm.remove(c,c+1) == false);
            assert(smm.remove(c,c) == true);
		}
        else{
              assert(smm.remove(c,c+2) == true);
        }
	}    
	assert(smm.size() == 0);
}

void testRemove() {
	testRemoveSearch(asc);
	testRemoveSearch(desc);
}

vector<int> randomKeys(int kMin, int kMax) {
	vector<int> keys;
	for (int c = kMin; c <= kMax; c++) {
		keys.push_back(c);
	}
	int n = keys.size();
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		swap(keys[i], keys[j]);
	}
	return keys;
}


void testIterator(Relation r) {
	SortedMultiMap smm = SortedMultiMap(r);
	SMMIterator it = smm.iterator();
	assert(!it.valid());
	it.first();
	assert(!it.valid());
	int cMin = 100;
	int cMax = 300;
	vector<int> keys = randomKeys(cMin, cMax);
	int n = keys.size();
	for (int i = 0; i < n; i++) {
      smm.add(keys[i], 100);
	  if (keys[i]%2==0)	{
		smm.add(keys[i], 200);
	  }
	}

	SMMIterator itsmm = smm.iterator();
	assert(itsmm.valid());
	itsmm.first();
	assert(itsmm.valid());

	TKey kPrev = itsmm.getCurrent().first;

    itsmm.next();
	while (itsmm.valid()) {
		TKey k = itsmm.getCurrent().first;
		assert(r(kPrev, k));
		kPrev = k;
		itsmm.next();
	}
}

void testIterator() {
	testIterator(asc);
	testIterator(desc);
}

void testAllExtended() {
//	testCreate();
//	testSearch();
//	testRemove();
//	testIterator();

	SortedMultiMap smm(asc);
	for(int i = 0; i < 5; i++)
    {
	    smm.add(5, i);
    }
	smm.add(8, 4);
	smm.add(1, 4);

	auto values = smm.removeKey(5);
	assert(values.size() == 5);
	assert(smm.size() == 2);

	SortedMultiMap smm2(asc);
	smm2.add(5, 6);
	smm2.add(3, 1);
	smm2.add(4, 2);
	smm2.add(4, 5);
	smm2.add(9, 4);
	smm2.remove(5, 6);
	assert(smm2.search(4).size() == 2);
}
