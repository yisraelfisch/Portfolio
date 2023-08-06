/*********************************
 * Reviewer: 
 * Author: yisrael fisch
 * File: semaphore.hpp
 * ******************************/

#include "semaphore.hpp"

namespace ilrd
{

Semaphore :: Semaphore(int count): m_count(count)
{}

void Semaphore:: Post()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    __atomic_add_fetch (&m_count, 1, __ATOMIC_SEQ_CST);
    lock.unlock();
    m_cond.notify_one();
}

void Semaphore:: Wait()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    while(!m_count)
    {
        m_cond.wait(lock);
    }
    __atomic_sub_fetch (&m_count, 1, __ATOMIC_SEQ_CST);
}
 
}//namespace ilrd
