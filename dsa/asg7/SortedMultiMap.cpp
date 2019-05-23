//
// Created by andreib on 22.05.2019.
//

#include <assert.h>
#include "SortedMultiMap.h"

// Theta(1)
SortedMultiMap::SortedMultiMap(Relation r) {
    capacity = 100;
    compare = r;
    count = 0;
    tree = new TElem [capacity];
    std::fill(tree+0, tree+capacity, EMPTY_ELEM);
}

// Recursively shift nodes in subtree due to a removal
// O(n)
void SortedMultiMap::recursiveDelete(int idx)
{
    // Node to be removed is a leaf
    if(
            (RIGHT_CHILD(idx) >= capacity || tree[RIGHT_CHILD(idx)] == EMPTY_ELEM) &&
            (LEFT_CHILD(idx) >= capacity || tree[LEFT_CHILD(idx)] == EMPTY_ELEM))
    {
        tree[idx] = EMPTY_ELEM;
        return;
    }

    int rIdx;
    // Bring the largest node smaller than the node to be promoted
    if (LEFT_CHILD(idx) < capacity && tree[LEFT_CHILD(idx)] != EMPTY_ELEM)
    {
        rIdx = LEFT_CHILD(idx);
        assert(tree[rIdx] != EMPTY_ELEM);
        while (RIGHT_CHILD(rIdx) < capacity && tree[RIGHT_CHILD(rIdx)] != EMPTY_ELEM)
        {
            rIdx = RIGHT_CHILD(rIdx);
        }
    }
    // No left branch, bring the smallest grater than the one to be promoted
    else
    {
        assert(RIGHT_CHILD(idx) < capacity);
        assert(tree[RIGHT_CHILD(idx)] != EMPTY_ELEM);
        rIdx = RIGHT_CHILD(idx);
        assert(tree[rIdx] != EMPTY_ELEM);
        while(LEFT_CHILD(rIdx) < capacity && tree[LEFT_CHILD(rIdx)] != EMPTY_ELEM)
        {
            rIdx = LEFT_CHILD(rIdx);
        }
    }
    tree[idx] = tree[rIdx];
    recursiveDelete(rIdx);
}

// Theta(n)
void SortedMultiMap::resize()
{
    int newCap = capacity * 4;
    auto* newTree = new TElem [newCap];
    std::fill(newTree+0, newTree+newCap, EMPTY_ELEM);
    std::copy(tree+0, tree+capacity, newTree+0);
    delete[] tree;
    capacity = newCap;
    tree = newTree;
}

// O(D)
int SortedMultiMap::locateKey(TKey c) const
{
    int idx = 1;
    while(idx < capacity && tree[idx] != EMPTY_ELEM && tree[idx].first != c)
    {
        if(compare(c, tree[idx].first)) idx = LEFT_CHILD(idx);
        else idx = RIGHT_CHILD(idx);
    }

    if (idx >= capacity) return NULL_VAL;

    return idx;
}

// O(D)
void SortedMultiMap::add(TKey c, TValue v)
{
    auto p = std::make_pair(c, v);
    int idx = 1;
    while(tree[idx] != EMPTY_ELEM)
    {
        if(compare(c, tree[idx].first)) idx = LEFT_CHILD(idx);
        else idx = RIGHT_CHILD(idx);

        if(idx >= capacity) resize();
    }
    tree[idx] = p;
    count += 1;
}

// O(D)
vector<TValue> SortedMultiMap::search(TKey c) const
{
    std::vector<TValue> values{};
    // find the first key equal with c
    int idx = locateKey(c);

    // Tree does not contain key c
    if(idx == NULL_VAL || tree[idx] == EMPTY_ELEM) return values;

    /*
     At least one value associated with `c`
     Due to the comparison function, values associated to c will
     always be on left branch
    */
    while(idx < capacity && tree[idx] != EMPTY_ELEM && tree[idx].first == c) {
        values.push_back(tree[idx].second);
        idx = LEFT_CHILD(idx);
    }

    return values;
}

// O(D)
bool SortedMultiMap::remove(TKey c, TValue v)
{
    int idx = locateKey(c);

    // Key does not exist
    if(idx == NULL_VAL || tree[idx] == EMPTY_ELEM) return false;

    // Find the exact pair
    auto p = std::make_pair(c, v);
    while(tree[idx].first == c && tree[idx] != p)
    {
        idx = LEFT_CHILD(idx);
    }

    // Pair does not exist
    if(tree[idx] != p) return false;

    /* Here comes the fun part
     * We will promote each of the right children by one level
     * in order to replace the node to be removed
     * Since any right child compares greater to the former
     * occupant, the left branch will not suffer modifications
     * If the last node to be promoted happens to have a left branch,
     * we will replace the promoted node with the largest node smaller
     * than jim
     * Are you not entertained??
    */

    recursiveDelete(idx);
    count -= 1;
    return true;
}

// Theta(1)
int SortedMultiMap::size() const
{
    return count;
}

// Theta(1)
bool SortedMultiMap::isEmpty() const
{
    return count == 0;
}

// Theta(1)
SMMIterator SortedMultiMap::iterator() const
{
    return SMMIterator(*this);
}

// Theta(n)
SortedMultiMap::~SortedMultiMap()
{
    delete[] tree;
}