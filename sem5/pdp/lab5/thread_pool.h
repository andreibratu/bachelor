//
// Kudos to ~rlupsa
//

#ifndef LAB5_THREAD_POOL_H
#define LAB5_THREAD_POOL_H

#include <cstddef>
#include <vector>
#include <functional>
#include <condition_variable>
#include <thread>
#include <list>
#include <atomic>

class ThreadPool
{
public:
    size_t count;

    explicit ThreadPool(size_t nrThreads)
            : m_end(false),
              m_liveThreads(nrThreads),
              count(nrThreads)
    {
        m_threads.reserve(nrThreads);
        for(size_t i = 0 ; i < nrThreads ; i++)
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

    int available_threads() {
        std::unique_lock<std::mutex> lck(m_mutex);
        return count - m_liveThreads; // NOLINT(cppcoreguidelines-narrowing-conversions)
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

    std::shared_ptr<std::atomic<bool>> enqueue(const std::function<void()>& func) {
        std::unique_lock<std::mutex> lck(m_mutex);
        auto readyFlag = std::make_shared<std::atomic<bool>>(false);
        m_queue.emplace_back([&func, &readyFlag](){
            func();
            (*readyFlag) = true;
        });
        m_cond.notify_one();
        return readyFlag;
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
                    m_liveThreads--;
                    if(m_liveThreads == 0)
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

#endif //LAB5_THREAD_POOL_H
