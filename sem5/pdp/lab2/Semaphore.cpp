//
// Created by bratu on 10/19/2020.
//

#include "Semaphore.h"

void Semaphore::acquire() {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [this] { return avail > 0; });
    avail--;
    lk.unlock();
}

void Semaphore::release() {
    m.lock();
    avail++;
    m.unlock();
    cv.notify_one();
}

Semaphore::Semaphore(const size_t &num_permissions) : num_permissions(num_permissions), avail(num_permissions) { }

size_t Semaphore::available() const { return avail; }

Semaphore::Semaphore(const Semaphore &s) : num_permissions(s.num_permissions), avail(s.avail) { }
