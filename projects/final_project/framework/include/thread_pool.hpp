/*********************************
 * Reviewer: 
 * Author: yisrael fisch
 * File: thread_pool.hpp
 * ******************************/
#pragma once

#include <vector>    /* std::vector */
#include <thread>    /* std::thread */
#include <future>    /* std::async std::future */
#include <memory>
#include <mutex>
#include <condition_variable>

#include "BtsQueue.hpp"
#include "semaphore.hpp"
#include "function.hpp"

namespace ilrd
{

class ThreadPool
{

public:
    class Future;

    explicit ThreadPool(int num_of_threads = 1);
    ~ThreadPool();
    Future Async(const Function<int(void)>& function);
    
    void ShutDown();    // terminate New tasks! finishes what currently in queue
    void Cancel();        // cancel all tasks and empties the queue
    
    ThreadPool(const ThreadPool& other) = delete;
    void operator=(const ThreadPool& other) = delete;

private:
    class Task;
    class Compare
    {
    public:
        bool operator() (const std::shared_ptr<Task> &, const std::shared_ptr<Task> &)
        {
            return true;
        } 
    };
    std::vector<std::thread> m_threads;
    BtsQueue<std::shared_ptr<Task>, Compare > m_tasks;
    /* Function<int(void)> insted off function*/
    void TaskDespacher();
    int m_keep_running;
    
}; //class thread pool

class ThreadPool::Future
{
public:
    explicit Future(const std::shared_ptr<Task> &s_ptr = nullptr);
    int Wait() const;
    
private:
    std::shared_ptr<Task> m_ptr;
};



} // namespace ilrd

