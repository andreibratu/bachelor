//
// Created by bratu on 10/19/2020.
//

#ifndef LAB2_SEMAPHORE_H
#define LAB2_SEMAPHORE_H

#include <cstddef>
#include <mutex>
#include <condition_variable>

class Semaphore
{
    const size_t num_permissions;
    size_t avail;
    std::mutex m;
    std::condition_variable cv;
    public:
        /** Default constructor. Default semaphore is a binary semaphore **/
        explicit Semaphore(const size_t& num_permissions = 1);

        /** Copy constructor. Does not copy state of mutex or condition variable,
            only the number of permissions and number of available permissions **/
        Semaphore(const Semaphore& s);

        void acquire();

        void release();

        [[nodiscard]] size_t available() const;
};


#endif //LAB2_SEMAPHORE_H
