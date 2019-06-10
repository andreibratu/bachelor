#include "Map.h"
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <cmath>

#define EMPTY_ELEM (std::make_pair(INT_MIN, INT_MIN))

Map::Map()
{
    capacity = 100;
    values = new TElem [capacity];
    next = new int [capacity];
    std::fill(values+0, values+capacity, EMPTY_ELEM);
    std::fill(next+0, next+capacity, NULL_TVALUE);
    firstFree = 0;
    count = 0;
}

void Map::resize()
{
    int newCapacity = capacity * 2;
    auto* newValues = new TElem [newCapacity];
    auto* newNext = new int [newCapacity];
    auto auxValues = new TElem [capacity];

    std::fill(newValues+0, newValues+newCapacity, EMPTY_ELEM);
    std::fill(newNext+0, newNext+newCapacity, NULL_TVALUE);
    std::copy(values+0, values+capacity, auxValues+0);

    delete[] values;
    delete[] next;

    int oldCount = 0;
    values = newValues;
    next = newNext;
    count = 0;
    capacity = newCapacity;

    // Rehash
    for(int i = 0; i < capacity / 2; i++)
    {
        assert(auxValues[i] != EMPTY_ELEM);
        if(auxValues[i] == EMPTY_ELEM) continue;
        oldCount = count;
        add(auxValues[i].first, auxValues[i].second);
        assert(count == oldCount + 1);
    }

    delete[] auxValues;
}

void Map::changeFirstFree()
{
    int pos = 0;
    while(pos < capacity && values[pos] != EMPTY_ELEM)
    {
        pos++;
    }
    firstFree = pos;
}

TValue Map::add(TKey c, TValue v)
{
    int oldCount = count;
    auto p = std::make_pair(c, v);
    int i = hash(c);

    // Handle first hash position special case
    if (values[i] == EMPTY_ELEM)
    {
        values[i] = p;
        count++;
        assert(count == oldCount + 1);
        changeFirstFree();
        return NULL_TVALUE;
    }
    if (values[i].first == c)
    {
        TElem old = values[i];
        values[i] = p;
        assert(oldCount == count);
        assert(count < capacity);
        changeFirstFree();
        return old.second;
    }
    int current = i;
    while (values[current].first != c && next[current] != NULL_TVALUE)
    {
        current = next[current];
    }
    if (values[current].first == c)
    {
        TElem old = values[current];
        values[current] = p;
        assert(count == oldCount);
        assert(count < capacity);
        changeFirstFree();
        return old.second;
    }
    if (firstFree == capacity) resize();
    count++;
    values[firstFree] = p;
    next[firstFree] = NULL_TVALUE;
    next[current] = firstFree;
    changeFirstFree();
    return NULL_TVALUE;
}

TValue Map::remove(TKey c)
{
    int i = hash(c);
    int j = NULL_TVALUE;
    int idx = 0;

    assert(i >= 0);

    while(idx < capacity && j == NULL_TVALUE)
    {
        if(next[idx] == i) j = idx;
        else idx++;
    }

    while(i != NULL_TVALUE && values[i].first != c)
    {
        j = i;
        i = next[i];
    }

    if (i == NULL_TVALUE) return NULL_TVALUE;
    else
    {
        int old = values[i].second;
        bool over = false;
        do
        {
            int p = next[i];
            int pp = i;
            while(p != NULL_TVALUE && hash(values[p].first) != i)
            {
                pp = p;
                p = next[p];
            }
            if(p == NULL_TVALUE) over = true;
            else
            {
                values[i] = values[p];
                j = pp;
                i = p;
            }
        } while(!over);
        if (j != NULL_TVALUE)
        {
            next[j] = next[i];
        }
        values[i] = EMPTY_ELEM;
        next[i] = NULL_TVALUE;
        if(firstFree > i) firstFree = i;

        count -= 1;
        return old;
    }
}

TValue Map::search(TKey c) const
{
    int i = hash(c);

    while(i != NULL_TVALUE && values[i].first != c)
    {
        i = next[i];
    }

    if(i == NULL_TVALUE) return NULL_TVALUE;

    return values[i].second;
}

// Theta(1)
int Map::size() const
{
    return count;
}

// Theta(1)
bool Map::isEmpty() const
{
    return count == 0;
}

MapIterator Map::iterator() const
{
    return MapIterator(*this);
}

// Theta(n)
Map::~Map() {
    delete[] next;
    delete[] values;
}

// Theta(1)
int Map::hash(TKey k) const
{
    return abs(k) % (capacity);
}

// Theta(n)
void Map::filter(Condition cond) {
    for(int i = 0; i < capacity;)
    {
        if(values[i] != EMPTY_ELEM && cond(values[i].first))
        {
            remove(values[i].first);
        }
        else
        {
            i++;
        }
    }
}
