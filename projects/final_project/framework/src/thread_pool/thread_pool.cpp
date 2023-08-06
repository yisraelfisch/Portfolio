/*********************************
 * Reviewer: 
 * Author: yisrael fisch
 * File: thread_pool.cpp
 * ******************************/

#include "thread_pool.hpp"
#include "semaphore.hpp"
#include "function.hpp"

#define BAD_APPLE 770


namespace ilrd
{

class ThreadPool::Task
{
public:
    Task(const Function<int(void)>& function, int priority = 0);
    void Run();
    void PostSem();
    void WaitSem();
    int GetPriorty()const;
    int GetStatus()const;


private:
    Function<int(void)> m_function;
    int m_status;
    int m_priority;
    Semaphore m_sem;
};//class Task

//---------------------------thread pool funcs------------------------
int BadApple(int arg)
{
    (void)arg;
    return BAD_APPLE;
}

ThreadPool::ThreadPool(int num_of_threads): m_keep_running(1)
{
    for(int i = 0; i < num_of_threads; ++i)
    {
        m_threads.push_back(std::thread(&ThreadPool::TaskDespacher,this));
    }
}

ThreadPool::~ThreadPool()
{
    if(m_threads.empty() == false)
    {
        ShutDown();
    }
    
}

ThreadPool::Future ThreadPool::Async(const Function<int(void)> &function)
{
    std::shared_ptr<Task> shared_ptr(new Task(function));
    m_tasks.Enqueue(shared_ptr);
    return Future(shared_ptr);
}

void ThreadPool::ShutDown()
{
    int num_of_threads = m_threads.size();
    for(int i = 0; i < num_of_threads; ++i)
    {
        Async(Function<int(void)>(&BadApple, i));
    }

    for(int i = 0; i < num_of_threads; ++i)
    {
        m_threads[i].join();
    }

    m_threads.clear();

}

void ThreadPool::Cancel()
{
    m_tasks.Clear();
    ShutDown();
}

void ThreadPool::TaskDespacher()
{
    std::shared_ptr<Task> shared_ptr;
    while(m_keep_running != BAD_APPLE)
    {
        m_tasks.Dequeue(shared_ptr);
        shared_ptr->Run();
        shared_ptr->PostSem();
        m_keep_running = shared_ptr->GetStatus();
    }
}

//---------------------------task funcs------------------------

ThreadPool::Task::Task(const Function<int(void)> &function, int priority):
m_function(function), m_status(0), m_priority(priority)
{
}

void ThreadPool::Task::Run()
{
    m_status = m_function();
}

void ThreadPool::Task::PostSem()
{
    m_sem.Post();
}

void ThreadPool::Task::WaitSem()
{
    m_sem.Wait();
}

int ThreadPool::Task::GetPriorty() const
{
    return m_priority;
}

int ThreadPool::Task::GetStatus() const
{
    return m_status;
}

//---------------------------future funcs------------------------

ThreadPool::Future::Future(const std::shared_ptr<Task> &s_ptr): m_ptr(s_ptr)
{
}

int ThreadPool::Future::Wait() const
{
    m_ptr->WaitSem();

    return m_ptr->GetStatus();
}
}
