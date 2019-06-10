#include <assert.h>
#include "KPriorityQueue.h"
#include "TestP9.h"
#include <vector>
#include <exception>
#include <iostream>

using namespace std;

bool rel2(TPriority p1, TPriority p2) {
    return p1 <= p2;
}

bool rel1(TPriority p1, TPriority p2) {
    return p1 >= p2;
}

void testCreate1() {
    KPriorityQueue pq(rel2, 3);
    assert(pq.atMostKMinusOne());
    try {
        pq.top();
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
    try {
        pq.pop();
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
    pq.push(5, 5);
    assert(pq.atMostKMinusOne());
    try {
        pq.top();
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
    try {
        pq.pop();
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
}

void testPush1() {
    KPriorityQueue pq(rel2, 3);
    for (int i = 0; i < 10; i++) {
        pq.push(i, i);
    }
    assert(false);
    assert(pq.atMostKMinusOne() == false);
    for (int i = -10; i < 20; i++) {
        pq.push(i, i);
    }
    assert(pq.atMostKMinusOne() == false);
    for (int i = -100; i < 100; i++) {
        pq.push(i, i);
    }
    assert(pq.atMostKMinusOne() == false);

    for (int i = -1000; i <= 1000; i++) {
        pq.push(i, i);
    }
    assert(pq.atMostKMinusOne() == false);
    assert(pq.top().second != 1000);
    assert(pq.top().second == -998);

    assert(pq.pop().second == -998);
    assert(pq.top().second == -997);
    for (int i = -997; i <= -100; i++) {
        assert(pq.top().second == i);
        assert(pq.pop().second == i);
    }
}

void testPop1() {
    KPriorityQueue pq(rel2, 3);
    for (int i = 0; i < 10; i++) {
        pq.push(i, i);
    }
    assert(pq.top().second == 2);
    assert(!pq.atMostKMinusOne());
    for (int i = -10; i < 20; i++) {
        pq.push(i, i);
    }
    assert(pq.top().second == -8);
    for (int i = 100; i > 50; i--) {
        pq.push(i, i);
    }
    assert(pq.top().second == -8);
    for (int i = -10; i < -1; i++) {
        assert(pq.pop().second == i+2);
    }

    assert(pq.pop().second == 0);
    for (int i = 0; i < 8; i++) {
        assert(pq.pop().second == i+1);
        assert(pq.pop().second == i+1);
    }
    assert(pq.pop().second == 9);
    assert(pq.pop().second == 9);

    for (int i = 10; i < 19; i++) {
        assert(pq.pop().second == i);
    }
    assert(pq.pop().second == 19);
    for (int i = 51; i <= 100; i++) {
        assert(pq.pop().second == i);
    }

    assert(pq.atMostKMinusOne() == true);

}

void testQuantity1(Relation rel) {//add a lot of elements
    KPriorityQueue pq(rel, 3);
    for (int i = 1; i <= 10; i++) {
        for (int j = 100; j >= -100; j --) {
            pq.push(j, j);
        }
    }
    int count = 1;
    Element last = pq.pop();
    while (pq.atMostKMinusOne() == false) {
        Element current = pq.pop();
        assert(rel(last.second, current.second));
        count++;
        last = current;
    }
    assert(count == 2008);
}

void testCreate2() {
	KPriorityQueue pq(rel2, 2);
	assert(pq.atMostKMinusOne() == true);
	try {
		pq.top();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		pq.pop();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	pq.push(5, 5);
	assert(pq.atMostKMinusOne() == true);
	try {
		pq.top();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		pq.pop();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
}

void testPush2() {
	KPriorityQueue pq(rel2, 2);
	for (int i = 0; i < 10; i++) {
		pq.push(i, i);
	}
	assert(pq.atMostKMinusOne() == false);
	for (int i = -10; i < 20; i++) {
		pq.push(i, i);
	}
	assert(pq.atMostKMinusOne() == false);
	for (int i = -100; i < 100; i++) {
		pq.push(i, i);
	}
	assert(pq.atMostKMinusOne() == false);

	for (int i = -1000; i <= 1000; i++) {
		pq.push(i, i);
	}
	assert(pq.atMostKMinusOne() == false);
	assert(pq.top().second != 1000);
	assert(pq.top().second == -999);

	assert(pq.pop().second == -999);
	assert(pq.top().second == -998);
	for (int i = -998; i >= 100; i--) {
		assert(pq.top().second == i);
		assert(pq.pop().second == i);
	}
}

void testPop2() {
	KPriorityQueue pq(rel2, 2);
	for (int i = 0; i < 10; i++) {
		pq.push(i, i);
	}
	assert(pq.top().second == 1);
	assert(pq.atMostKMinusOne() == false);
	for (int i = -10; i < 20; i++) {
		pq.push(i, i);
	}
	assert(pq.top().second == -9);
	for (int i = 100; i > 50; i--) {
		pq.push(i, i);
	}
	assert(pq.top().second == -9);


	for (int i = -10; i < 0; i++) {
		assert(pq.pop().second == i+1);
	}
	assert(pq.pop().second == 0);
	for (int i = 0; i < 9; i++) {
		assert(pq.pop().second == i+1);
		assert(pq.pop().second == i+1);
	}
	assert(pq.pop().second == 10);
	for (int i = 10; i < 18; i++) {
		assert(pq.pop().second == i+1);
	}
	assert(pq.pop().second == 19);
	for (int i = 51; i <= 100; i++) {
		assert(pq.pop().second == i);
	}

	assert(pq.atMostKMinusOne() == true);

}

void testQuantity2(Relation rel) {
	KPriorityQueue pq(rel, 2);
	for (int i = 1; i <= 10; i++) {
		for (int j = 500; j >= -500; j --) {
			pq.push(j, j);
		}
	}
	int count = 1;
	Element last = pq.pop();
	while (pq.atMostKMinusOne() == false) {
		Element current = pq.pop();
		assert(rel(last.second, current.second));
		count++;
		last = current;
	}
	assert(count == 10009);
}



void testP9() {
    testCreate1();
    testPush1();
    testPop1();
    testQuantity1(rel2);
    testQuantity1(rel1);
    testCreate2();
    testPush2();
    testPop2();
    testQuantity2(rel2);
    testQuantity2(rel1);
}
