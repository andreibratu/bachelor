//
// Created by bratu on 10/20/2020.
//

#ifndef LAB3_THREADPOOL_H
#define LAB3_THREADPOOL_H

#include <cstddef>
#include <vector>
#include <functional>
#include <condition_variable>
#include <thread>
#include <list>

class ThreadPool
{
public:
    explicit ThreadPool(size_t nrThreads)
            :m_end(false),
             m_liveThreads(nrThreads)
    {
        m_threads.reserve(nrThreads);
        for(size_t i=0 ; i<nrThreads ; ++i)
        {
            m_threads.emplace_back([this](){this->run();});
        }
    }

    ~ThreadPool()
    {
        close();
        for(std::thread& t : m_threads)
        {
            t.join();
        }
    }

    void close() {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_end = true;
        m_cond.notify_all();
        while(m_liveThreads > 0)
        {
            m_condEnd.wait(lck);
        }
    }

    void enqueue(const std::function<void()>& func) {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_queue.push_back(func);
        m_cond.notify_one();
    }

private:
    void run()
    {
        while(true)
        {
            std::function<void()> toExec;
            {
                std::unique_lock<std::mutex> lck(m_mutex);
                while(m_queue.empty() && !m_end)
                {
                    m_cond.wait(lck);
                }
                if(m_queue.empty())
                {
                    --m_liveThreads;
                    if(0 == m_liveThreads)
                    {
                        m_condEnd.notify_all();
                    }
                    return;
                }
                toExec = std::move(m_queue.front());
                m_queue.pop_front();
            }
            toExec();
        }
    }

    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::condition_variable m_condEnd;
    std::list<std::function<void()> > m_queue;
    bool m_end;
    size_t m_liveThreads;
    std::vector<std::thread> m_threads;
};

#endif //LAB3_THREADPOOL_H
