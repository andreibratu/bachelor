//
// Created by andreib on 22.05.2019.
//

#include "SMMIterator.h"


// Theta(n)
void SMMIterator::traverse(int cIdx)
{
    int left = this->container.tree[cIdx].leftChild;
    int right = this->container.tree[cIdx].rightChild;
    if(left == NULL_VAL && right == NULL_VAL)
    {
        traversal.push_back(cIdx);
        return;
    }
    if(left != NULL_VAL)
    {
        traverse(left);
    }
    traversal.push_back(cIdx);
    if(right != NULL_VAL)
    {
        traverse(right);
    }
}

// Theta(n)
SMMIterator::SMMIterator(const SortedMultiMap &c): container{c}
{
    if(container.size() >= 1) traverse(0);
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
    return container.tree[traversal[idx]].value;
}

