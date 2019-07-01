#include <assert.h>
#include <exception>

#include "ExtendedTest.h"
#include "IndexedList.h"
#include "ListIterator.h"

using namespace std;

void testCreate() {
    IndexedList list = IndexedList();
    assert(list.isEmpty());
    ListIterator it = list.iterator();
    assert(!it.valid());
    try {
        it.next();
        assert(false);
    } catch (exception &) {
        assert(true);
    }
    assert(list.size() == 0);
}

void testAdd() {
    IndexedList list = IndexedList();
    list.addToEnd(1);
    assert(!list.isEmpty());
    assert(list.size() == 1);
    assert(list.getElement(0) == 1);
    try {
        list.getElement(2);
        assert(false);
    } catch (exception&){
        assert(true);
    }

    for (int i = 0; i <= 100; i ++){
        list.addToEnd(i);
        list.addToPosition(list.size() - 1,i);
        try {
            list.addToPosition((i+2)*2,i);
            assert(false);
        } catch (exception&){
            assert(true);
        }

        assert(list.size() == 2*(i+1) + 1);
    }
    ListIterator it = list.iterator();
    assert(it.getCurrent() == 1);
    it.next();
    int i = 0;
    while (it.valid()){
        assert(it.getCurrent() == i);
        it.next();
        assert(it.getCurrent() == i);
        it.next();
        i++;
    }
    assert(!it.valid());
    try {
        it.getCurrent();
        assert(false);
    } catch (exception&){
        assert(true);
    }
    it.first();
    assert(it.valid());
    assert(it.getCurrent() == 1);

    i = 1;
    int v = 0;
    while (i < list.size()){
        assert(list.getElement(i) == v);
        i++;
        i++;
        v++;
    }
}

void testSetRemoveSearch() {
    IndexedList list = IndexedList();
    for (int i = 0; i <= 100; i ++){
        list.addToEnd(i);
    }
    assert(list.size() == 101);
    assert(list.search(50) == 50);
    assert(list.search(100) == 100);
    assert(list.remove(100) == 100);
//    try {
//        list.remove(100);
//        assert(false);
//    } catch (exception&){
//        assert(true);
//    }
    assert(list.size() == 100);
    assert(list.search(100) == -1);
    assert(list.search(99) == 99);
    int v = 99;
    for (int i = 0; i < 100; i++){
        list.setElement(i,v);
        v--;
    }
    assert(list.getElement(99) == 0);
    assert(list.search(99) == 0);
    assert(list.search(0) == 99);
    assert(list.search(50) == 49);
//    try {
//        list.setElement(v,v);
//        assert(false);
//    } catch (exception&){
//        assert(true);
//    }
    ListIterator it = list.iterator();
    for (int i = 99; i > -1; i--){
        assert(it.getCurrent() == i);
        it.next();
    }
    assert(!it.valid());
    for (int i = 99; i > -1; i--){
        list.remove(i);
        assert(list.size() == i);
    }
    assert(list.isEmpty());
    assert(list.size() == 0);
    it.first();
    assert(!it.valid());
}

void testAllExtended() {
    testCreate();
    testAdd();
    testSetRemoveSearch();
}
