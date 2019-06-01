//
// Created by andreib on 22.05.2019.
//

#include <assert.h>
#include "SortedMultiMap.h"

// Theta(1)
SortedMultiMap::SortedMultiMap(Relation r)
{
    capacity = 100;
    freeSpace = Stack(capacity);
    for(int i = 0; i < capacity; i++) freeSpace.push(i);
    compare = r;
    count = 0;
    tree = new Node [capacity];
    std::fill(tree+0, tree+capacity, EMPTY_ELEM);
}

// Recursively shift nodes in subtree due to a removal
// O(n)
void SortedMultiMap::recursiveDelete(int idx)
{
    const Node& nodeToDelete = tree[idx];
    // Node to be removed is a leaf
    if(tree[idx].leftChild == NULL_VAL && tree[idx].rightChild == NULL_VAL)
    {
        // Tree only contains the root node
        if(nodeToDelete.parent == NULL_VAL)
        {
            tree[idx] = EMPTY_ELEM;
            freeSpace.push(idx);
            return;
        }

        // Generic leaf
        Node& parent = tree[nodeToDelete.parent];
        if(parent.leftChild == idx) parent.leftChild = NULL_VAL;
        else parent.rightChild = NULL_VAL;

        tree[idx] = EMPTY_ELEM;
        freeSpace.push(idx);
        return;
    }

    // Index of node to substitute `idx`
    int rIdx;

    // Go on left branch
    // Bring the largest node smaller than the node to be promoted
    if (tree[idx].leftChild != NULL_VAL)
    {
        rIdx = tree[idx].leftChild;
        while (tree[rIdx].rightChild != NULL_VAL)
        {
            rIdx = tree[rIdx].rightChild;
        }
    }
    // No left branch, go on right
    // No left branch, bring the smallest grater than the one to be promoted
    else
    {
        rIdx = tree[idx].rightChild;
        while(tree[rIdx].leftChild != NULL_VAL)
        {
            rIdx = tree[rIdx].leftChild;
        }
    }
    tree[idx].value = tree[rIdx].value;
    recursiveDelete(rIdx);
}

// Theta(n)
void SortedMultiMap::resize()
{
    int oldCap = capacity;
    int newCap = capacity * 4;
    auto* newTree = new Node [newCap];
    std::fill(newTree+0, newTree+newCap, EMPTY_ELEM);
    std::copy(tree+0, tree+capacity, newTree+0);
    delete[] tree;
    capacity = newCap;
    tree = newTree;
    freeSpace.resize(newCap);
    for(int i = oldCap; i < newCap; i++) freeSpace.push(i);
}

// O(D)
/**
 * Locate first appearance of key
 * @param c Searched key
 * @return NULL_VAL if not found or the index of the key
 */
int SortedMultiMap::locateKey(TKey c) const
{
    // The tree is empty
    if(count == 0) return NULL_VAL;

    // Use relation to look
    int idx = 0;
    while(idx != NULL_VAL && tree[idx].value.first != c)
    {
        if(compare(c, tree[idx].value.first)) idx = tree[idx].leftChild;
        else idx = tree[idx].rightChild;
    }

    // Key not found
    if (idx == NULL_VAL) return NULL_VAL;

    return idx;
}

// O(D)
/**
 * Insert key-value pair in the multimap
 * @param c The key
 * @param v The value
 */
void SortedMultiMap::add(TKey c, TValue v)
{
    auto p = std::make_pair(c, v);
    if(freeSpace.empty()) resize();

    int firstFree = freeSpace.pop();

    tree[firstFree] = {p, NULL_VAL, NULL_VAL, NULL_VAL};

    // Tree contained no nodes
    if(firstFree == 0)
    {
        count += 1;
        return;
    }

    // At least one node already in the tree
    int idx = 0;
    int previous = -1;
    while(idx != NULL_VAL)
    {
        previous = idx;
        if(compare(c, tree[idx].value.first)) idx = tree[idx].leftChild;
        else idx = tree[idx].rightChild;
    }
    if(compare(c, tree[previous].value.first))
    {
        tree[previous].leftChild = firstFree;
        tree[firstFree].parent = previous;
    }
    else
    {
        tree[previous].rightChild = firstFree;
        tree[firstFree].parent = previous;
    }
    count += 1;
}

// O(D)
/**
 * Return all values associated with given key
 * @param c The key
 * @return
 */
vector<TValue> SortedMultiMap::search(TKey c) const
{
    std::vector<TValue> values{};
    int idx = locateKey(c);

    // Key not found
    if(idx == NULL_VAL) return values;

    /*
     At least one value associated with `c`
     Due to the comparison function, values associated to c will
     always be on left branch
    */
    while(idx != NULL_VAL && tree[idx].value.first == c)
    {
        values.push_back(tree[idx].value.second);
        idx = tree[idx].leftChild;
    }

    return values;
}

// O(D)
bool SortedMultiMap::remove(TKey c, TValue v)
{
    int idx = locateKey(c);

    // Key does not exist
    if(idx == NULL_VAL) return false;

    // Find the exact pair
    while(idx != NULL_VAL && tree[idx].value.first == c && tree[idx].value.second != v)
    {
        idx = tree[idx].leftChild;
    }

    // Pair does not exist
    if(idx == NULL_VAL || tree[idx].value.first != c) return false;

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

std::vector<TValue> SortedMultiMap::removeKey(TKey key) {
    int idx = locateKey(key);
    std::vector<int> values{};

    // No such key
    if(idx == NULL_VAL) return values;

    while(idx != NULL_VAL)
    {
        values.push_back(tree[idx].value.second);
        remove(tree[idx].value.first, tree[idx].value.second);

        // If node promoted by removal does not have key `key`, look up
        // the next node that could given key
        if(tree[idx].value.first != key)
        {
            idx = tree[idx].leftChild;
        }
    }

    return values;
}
