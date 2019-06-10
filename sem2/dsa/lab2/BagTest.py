# -*- coding: utf-8 -*-
"""
Created on Tue Feb 19 16:07:06 2019

@author: Zsu
"""

from Bag import Bag
from BagIterator import BagIterator

def testAll():
    b = Bag()
    assert(b.size()  == 0)
    assert(b.isEmpty())

    b.add(4)
    b.add(11)
    b.add(4)
    b.add(77)
    b.add(8)

    assert(b.size() == 5)
    assert(b.isEmpty() == False)

    assert(b.remove(44) == False)
    assert(b.remove(11))
    assert(b.size() == 4)
    assert(b.nrOccurrences(4) == 2)
    assert(b.search(77))
    assert(b.search(13) == False)

    itb = b.iterator()
    assert(itb.valid())
    cont = 0
    while (itb.valid()):
        cont += 1
        e = itb.getCurrent()
        itb.next()
        assert(b.search(e))
    assert(cont == b.size())
    itb.first()
    assert(itb.valid())

testAll()
