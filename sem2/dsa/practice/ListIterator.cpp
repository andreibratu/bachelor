//
// Created by andreib on 26.06.2019.
//

#include <bits/exception.h>
#include "ListIterator.h"

ListIterator::ListIterator(const IndexedList &c): container{c}
{
    it = container.head;
}

void ListIterator::first()
{
    it = container.head;
}

void ListIterator::next()
{
    if (!valid()) throw std::exception();

    it = container.next[it];
}

bool ListIterator::valid() const
{
    return it != NIL;
}

TElem ListIterator::getCurrent() const
{
    if (!valid()) throw std::exception();

    return container.elements[it];
}


