//
// Created by andreib on 26.06.2019.
//

#include <bits/exception.h>
#include <algorithm>
#include "IndexedList.h"
#include "ListIterator.h"

void IndexedList::updateFreePos()
{
    freePos = 0;
    while (freePos < capacity && elements[freePos] != NIL)
    {
        freePos++;
    }
    if (freePos == capacity)
    {
        resize();
    }

}

void IndexedList::resize()
{
    int newCap = capacity*2;
    auto *newElements = new TElem [newCap];
    int *newNext = new int [newCap];

    std::fill(newElements+capacity, newElements+newCap, NIL);
    std::fill(newElements+capacity, newElements+newCap, NIL);
    std::copy(elements+0, elements+capacity, newElements+0);
    std::copy(next+0, next+capacity, newNext+0);

    delete[] elements;
    delete[] next;
    elements = newElements;
    next = newNext;
    capacity = newCap;
}

IndexedList::IndexedList()
{
    capacity = 100;
    elements = new TElem [capacity];
    next = new int [capacity];
    std::fill(elements+0, elements+capacity, NIL);
    std::fill(next+0, next+capacity, NIL);
    capacity = 100;
    count = 0;
    head = NIL;
    freePos = 0;
}

int IndexedList::size() const
{
    return count;
}

bool IndexedList::isEmpty() const
{
    return count == 0;
}

TElem IndexedList::getElement(int pos) const
{
    if (pos < 0 || pos >= count) throw std::exception();

    int it = head;
    for (int i = 0; i < pos; i++)
    {
        it = next[it];
    }
    return elements[it];
}

TElem IndexedList::setElement(int pos, TElem e)
{
    if (pos < 0 || pos >= count) throw std::exception();

    int it = head;
    for (int i = 0; i < pos; i++)
    {
        it = next[it];
    }
    TElem aux = elements[it];
    elements[it] = e;
    return aux;
}

void IndexedList::addToEnd(TElem e) {
    if (head == NIL)
    {
        elements[freePos] = e;
        next[freePos] = NIL;
        head = freePos;
    }
    else
    {
        int it = head;
        int itb = it;
        while(it != NIL)
        {
            itb = it;
            it = next[it];
        }
        elements[freePos] = e;
        next[freePos] = NIL;
        next[itb] = freePos;
    }

    count++;
    updateFreePos();
}

void IndexedList::addToPosition(int pos, TElem e)
{
    if (pos < 0 || pos >= count) throw std::exception();

    if (pos == 0)
    {
        elements[freePos] = e;
        next[freePos] = head;
        head = freePos;
    }
    else
    {
        int it = head;
        int itb = it;
        for (int i = 0; i < pos; i++)
        {
            itb = it;
            it = next[it];
        }

        elements[freePos] = e;
        next[freePos] = it;
        next[itb] = freePos;
    }

    count++;
    updateFreePos();
}

TElem IndexedList::remove(int pos)
{
    if (pos < 0 || pos >= count) throw std::exception();

    TElem old;

    if (pos == 0)
    {
        int cNode = head;
        head = next[head];
        old = elements[cNode];
        elements[cNode] = NIL;
        next[cNode] = NIL;

        freePos = std::min(cNode, freePos);
    }
    else
    {
        int it = head;
        int itb = it;
        for (int i = 0; i < pos; i++)
        {
            itb = it;
            it = next[it];
        }

        next[itb] = next[it];
        old = elements[it];
        elements[it] = NIL;
        next[it] = NIL;

        freePos = std::min(it, freePos);
    }

    count--;
    return old;
}

int IndexedList::search(TElem e) const
{
    int it = head;
    int pos = 0;
    while (it != NIL && elements[it] != e)
    {
        it = next[it];
        pos++;
    }

    if (it == NIL) return -1;

    return pos;
}

ListIterator IndexedList::iterator() const
{
    return ListIterator(*this);
}

IndexedList::~IndexedList()
{
    delete[] elements;
    delete[] next;
}

IndexedList::IndexedList(const IndexedList &other)
{
    capacity = other.capacity;
    count = other.count;
    head = other.head;
    freePos = other.freePos;
    elements = new TElem [other.capacity];
    next = new int [other.capacity];
    std::copy(other.elements+0, other.elements+capacity, elements+0);
    std::copy(other.next+0, other.next+capacity, next+0);
}

IndexedList &IndexedList::operator=(const IndexedList &other)
{
    capacity = other.capacity;
    count = other.count;
    head = other.head;
    freePos = other.freePos;
    elements = new TElem [other.capacity];
    next = new int [other.capacity];
    std::copy(other.elements+0, other.elements+capacity, elements+0);
    std::copy(other.next+0, other.next+capacity, next+0);

    return *this;
}











