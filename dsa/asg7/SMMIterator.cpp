//
// Created by andreib on 22.05.2019.
//

#include "SMMIterator.h"

// Theta(1)
// Equivalent to a NULL node check on a dynamic memory implementation
inline bool SMMIterator::posExists(int pos) const
{
    return pos < container.capacity;
}

// Theta(n)
void SMMIterator::traverse(int cIdx)
{
    if(
        (!posExists(LEFT_CHILD(cIdx)) || container.tree[LEFT_CHILD(cIdx)] == EMPTY_ELEM) &&
        (!posExists(RIGHT_CHILD(cIdx)) || container.tree[RIGHT_CHILD(cIdx)] == EMPTY_ELEM)
    )
    {
        traversal.push_back(cIdx);
        return;
    }
    if(posExists(LEFT_CHILD(cIdx)) && container.tree[LEFT_CHILD(cIdx)] != EMPTY_ELEM)
    {
        traverse(LEFT_CHILD(cIdx));
    }
    traversal.push_back(cIdx);
    if(posExists(RIGHT_CHILD(cIdx)) && container.tree[RIGHT_CHILD(cIdx)] != EMPTY_ELEM)
    {
        traverse(RIGHT_CHILD(cIdx));
    }
}

// Theta(n)
SMMIterator::SMMIterator(const SortedMultiMap &c): container{c}
{
    if(container.size() >= 1) traverse(1);
    idx = 0;
}

// Theta(1)
void SMMIterator::first()
{
    idx = 0;
}

// Theta(1)
void SMMIterator::next()
{
    if(!valid()) throw std::exception();
    idx++;
}

// Theta(1)
bool SMMIterator::valid() const
{
    return idx < traversal.size();
}

// Theta(1)
std::pair<int, int> SMMIterator::getCurrent() const
{
    if(!valid()) throw std::exception();
    return container.tree[traversal[idx]];
}

