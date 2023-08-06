/*********************************
 * Reviewer: 
 * Author: yisrael fisch
 * File: semaphore.hpp
 * ******************************/

#pragma once

#include <mutex>
#include <condition_variable>

namespace ilrd
{
    
class Semaphore 
{
public:
    Semaphore (int count = 0);
    void Post();
    void Wait();

private:
    std::mutex m_mtx;
    std::condition_variable m_cond;
    int m_count;
};

}//namespace ilrd
