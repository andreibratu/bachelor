# -*- coding: utf-8 -*-
"""
Created on Tue Feb 19 16:07:06 2019

@author: Zsu
"""

from Bag import Bag
from BagIterator import BagIterator

def testCreate():
    b = Bag()
    assert(b.size() == 0)
    assert(b.isEmpty() == True)
    for i in range(-5,5):
        assert(b.search(i) == False)
    for i in range(-10,10):
        assert(b.remove(i) == False)
    for i in range(-10,10):
        assert(b.nrOccurrences(i) == 0)

    it = b.iterator()
    assert(it.valid() == False)

def testAdd():

    b = Bag()
    for i in range(10):
        b.add(i)
    assert(b.isEmpty() == False)
    assert(b.size() == 10)
    for i in range(-10, 20):
        b.add(i)

    assert(b.isEmpty() == False)
    assert(b.size() == 40)
    for i in range(-100, 100):
        b.add(i)

    assert(b.isEmpty() == False)
    assert(b.size() == 240)
    for i in range(-200,200):
        count = b.nrOccurrences(i)
        if i < -100:
            assert(count == 0)
            assert(b.search(i) == False)
        elif i < -10:
            assert(count == 1)
            assert(b.search(i) == True)
        elif i < 0:
            assert(count == 2)
            assert(b.search(i) == True)
        elif i < 10:
            assert(count == 3)
            assert(b.search(i) == True)
        elif i < 20:
            assert(count == 2)
            assert(b.search(i) == True)
        elif i < 100:
            assert(count == 1)
            assert(b.search(i) == True)
        else:
            assert(count == 0)
            assert(b.search(i) == False)

    for i in range(10000, -10000, -1):
        b.add(i)

    assert(b.size() == 20240)


def testRemove():
    b = Bag()
    for i in range(-100,100):
        assert(b.remove(i) == False)

    assert(b.size() == 0)
    for i in range(-100,100, 2):
        b.add(i)

    for i in range (-100,100):
        if i % 2 == 0:
            assert(b.remove(i) == True)
        else :
            assert(b.remove(i) == False)

    assert(b.size() == 0)
    for i in range(-100,101, 2):
        b.add(i)
    for i in range(100,-100, -1):
        if i % 2 == 0:
            assert(b.remove(i) == True)
        else:
            assert(b.remove(i) == False)
    assert(b.size() == 1)
    b.remove(-100)
    for i in range(-100, 100):
        b.add(i)
        b.add(i)
        b.add(i)
        b.add(i)
        b.add(i)

    assert(b.size() == 1000)
    for i in range(-100,100):
        assert(b.nrOccurrences(i) == 5)

    for i in range(-100, 100):
        assert(b.remove(i) == True)

    assert(b.size() == 800)
    for i in range(-100, 100):
        assert(b.nrOccurrences(i) == 4)

    for i in range(-200, 200):
        if (i < -100) or (i >= 100):
            assert(b.remove(i) == False)
            assert(b.remove(i) == False)
            assert(b.remove(i) == False)
            assert(b.remove(i) == False)
            assert(b.remove(i) == False)
        else:
            assert(b.remove(i) == True)
            assert(b.remove(i) == True)
            assert(b.remove(i) == True)
            assert(b.remove(i) == True)
            assert(b.remove(i) == False)

    assert(b.size() == 0)
    for i in range(-1000,1000):
        assert(b.nrOccurrences(i) == 0)

    min = -200
    max = 200
    while min < max:
        b.add(min)
        b.add(max)
        min += 1
        max -= 1

    b.add(0)
    b.add(0)
    assert(b.size() == 402)
    for i in range(-30, 30):
        assert(b.search(i) == True)
        assert(b.remove(i) == True)
        if i != 0:
            assert(b.search(i) == False)
        else:
            assert(b.search(i) == True)

    assert(b.size() == 342)




def testIterator():
    b = Bag()
    it = b.iterator()
    assert(it.valid() == False)
    try:
        it.next()
        assert(False)
    except ValueError:
        assert (True)
    try:
        it.getCurrent()
        assert(False)
    except ValueError:
        assert(True)

    for i in range(0,100):
        b.add(33)

    it2 = b.iterator()
    assert(it2.valid() == True)
    for i in range(0, 100):
        elem = it2.getCurrent()
        assert(elem == 33)
        it2.next()

    assert(it2.valid() == False)
    it2.first()
    assert(it2.valid() == True)
    for i in range(0,100):
        elem = it2.getCurrent()
        elem2 = it2.getCurrent()
        assert(elem == 33)
        assert(elem2 == 33)
        it2.next()

    assert(it2.valid() == False)
    try:
        it2.next()
        assert(False)
    except ValueError:
        assert(True)

    try:
        it2.getCurrent()
        assert(False)
    except ValueError:
        assert(True)
    b2 = Bag()
    for i in range(-100, 100):
        b2.add(i)
        b2.add(i)
        b2.add(i)

    it3 = b2.iterator()
    assert(it3.valid() == True)
    for i in range(0, 600):
        e1 = it3.getCurrent()
        it3.next()

    assert(it3.valid() == False)
    it3.first()
    assert(it3.valid() == True)
    b3 = Bag()
    for i in range(0,200, 4):
        b3.add(i)

    it4 = b3.iterator()
    assert(it4.valid() == True)
    count = 0
    while it4.valid():
        e = it4.getCurrent()
        assert(e % 4 == 0)
        it4.next()
        count += 1

    assert(count == 50)
    b4 = Bag()
    for i in range(0, 100):
        b4.add(i)
        b4.add(i * (-2))
        b4.add(i * 2)
        b4.add(i / 2)
        b4.add(i / (-2))

    elements = []
    it5 = b4.iterator()
    while it5.valid():
        e = it5.getCurrent()
        elements.append(e)
        it5.next()

    assert(len(elements) == b4.size())
    for i in range(0, len(elements)):
        lastElem = elements[len(elements) - i - 1]
        assert(b4.search(lastElem) == True)
        b4.remove(lastElem)

    b5 = Bag()
    for i  in range(0, 100):
        b5.add(i)
        b5.add(i * (-2))
        b5.add(i * 2)
        b5.add(i / 2)
        b5.add(i / (-2))

    elements2 = []
    it6 = b5.iterator()
    while it6.valid():
        e = it6.getCurrent()
        elements2.append(e)
        it6.next()

    assert(len(elements2) == b5.size())
    for i in range(0, len(elements2)):
        firstElem = elements2[i]
        assert(b5.search(firstElem) == True)
        b5.remove(firstElem)


def testQuantity():
    b = Bag()
    print('Adding')
    for i in range(10, 0, -1):
        print(i)
        for j in range(-30000, 30000, i):
            b.add(j)

    assert(b.size() == 175739)
    assert(b.nrOccurrences(-30000) == 10)
    it = b.iterator()
    print('Dimension: ', b.size())
    print('Iterator')
    assert(it.valid() == True)
    for i in range(0, b.size()):
        it.next()

    it.first()
    print('Iterator 2')
    count = 0
    while it.valid():
        if count % 1000 == 0:
            print('  ', count)
        e = it.getCurrent()
        assert(b.search(e) == True)
        assert(b.nrOccurrences(e) > 0)
        it.next()
        count += 1

    assert(it.valid() == False)
    print('Remove')
    for i in range(0, 10):
        print(i)
        for j in range(40000, -40000-1, -1):
            b.remove(j)

    assert(b.size() == 0)



def testAllExtended():
    testCreate()
    testAdd()
    testRemove()
    testIterator()
    testQuantity()


testAllExtended()
