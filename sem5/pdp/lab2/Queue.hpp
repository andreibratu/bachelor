//
// Created by bratu on 10/19/2020.
//

#ifndef LAB2_QUEUE_HPP
#define LAB2_QUEUE_HPP


#include <cstddef>
#include "Semaphore.h"

template <typename T>
class Queue
{
private:
    const size_t size;
    T* const arr;
    int start = 0, end = 0;
    Semaphore write, read;
    std::recursive_mutex writemtx, readmtx;
public:
    explicit Queue(const size_t size = 1) :
        size(size), arr(new T[size]),
        write(size), read(0) { }

    virtual ~Queue()
    {
        delete[] arr;
    }

    void add(T obj)
    {
        std::lock_guard<std::recursive_mutex> lg(writemtx);
        write.acquire();
        arr[end++] = obj;
        end %= size;
        read.release();
    }

    bool offer(T obj)
    {
        std::lock_guard<std::recursive_mutex> lg(writemtx);
        if(!full())
        {
            add(obj);
            return true;
        }
        return false;
    }

    T take()
    {
        std::lock_guard<std::recursive_mutex> lg(readmtx);
        read.acquire();
        T val = arr[start++];
        start %= size;
        write.release();
        return val;
    }

    [[nodiscard]] bool empty() const
    {
        return !read.available();
    }

    [[nodiscard]] bool full() const
    {
        return !write.available();
    }
};


#endif //LAB2_QUEUE_HPP
