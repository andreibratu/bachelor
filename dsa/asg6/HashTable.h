//
// Created by andreib on 27.04.2019.
//

#ifndef ASG6_HASHTABLE_H
#define ASG6_HASHTABLE_H

#include <functional>
#include <iostream>

#define null -1

class Map;
class MapIterator;

template <class T>
class HashTable {

friend class Map;
friend class MapIterator;

private:
    T* array;
    int* next{};
    int firstFree{};
    int m{};
    int (*hash) (T);
    bool (*equality) (T, T);
    T empty_elem{};

    void updateFirstFree();

    void resize();
public:
    HashTable();

    explicit HashTable(int (*hash) (T), bool (*equality) (T, T), T empty_elem);

    void add(T k);

    T find(T elem) const;

    T remove(T elem);

    ~HashTable();
};

template<class T>
void HashTable<T>::resize() {
    T* new_array = new T [this->m * 2];
    int* new_next = new  int [this->m * 2];

    std::copy(this->next+0, this->next+this->m, new_next+0);
    std::copy(this->array+0, this->array+this->m, new_array+0);

    delete[] this->array;
    this->array = new_array;

    delete[] this->next;
    this->next = new_next;
}

template <class T>
void HashTable<T>::updateFirstFree() {
    while(
        this->firstFree < this->m &&
        !this->equality(this->array[this->firstFree], this->empty_elem)
    ) this->firstFree++;
}

template <class T>
HashTable<T>::HashTable() = default;

template <class T>
HashTable<T>::HashTable(int (*hash) (T), bool (*equality) (T, T), T empty_elem) {
    this->m = 200;
    this->firstFree = 47;
    this->hash = hash;
    this->equality = equality;
    this->empty_elem = empty_elem;

    this->array = new T [m];
    this->next = new int [m];

    std::fill(this->array+0, this->array+200, empty_elem);
    std::fill(this->next+0, this->next+200, -1);
}

template <class T>
void HashTable<T>::add(T k) {
    this->array[0] = {-1, -1};
    this->next[0] = -1;

    this->array[1] = {-1, -1};
    this->next[1] = -1;

    int pos = hash(k);

    if (this->equality(array[pos], empty_elem)) {
        array[pos] = k;
        next[pos] = null;
    }
    else {
        if(firstFree == m) {
            resize();
        }

        while(next[pos] != null) {
            pos = next[pos];
        }

        array[firstFree] = k;
        next[firstFree] = null;
        next[pos] = firstFree;

        updateFirstFree();
    }
}

template <class T>
T HashTable<T>::find(T elem) const {
    int pos = hash(elem);

    while(pos != null && !equality(array[pos], elem)) {
        pos = next[pos];
    }

    if(pos == null) return empty_elem;

    return array[pos];
}

template<class T>
T HashTable<T>::remove(T elem) {
    int pos = hash(elem);
    int nextPos = next[pos];

    if(equality(array[pos], elem)) {
        T aux = array[pos];
        array[pos] = empty_elem;

        return aux;
    }

    while(nextPos != null && !equality(array[nextPos], elem)) {
        pos = nextPos;
        nextPos = next[nextPos];
    }

    if(nextPos == null) return empty_elem;

    T aux = array[nextPos];
    array[nextPos] = empty_elem;
    next[pos] = next[nextPos];
    next[nextPos] = null;
    firstFree = std::min(firstFree, nextPos);

    return aux;
}

template<class T>
HashTable<T>::~HashTable() {
    delete[] array;
    delete[] next;
}

#endif //ASG6_HASHTABLE_H
