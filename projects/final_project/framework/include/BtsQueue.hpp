/*********************************
 * Reviewer: 
 * Author: yisrael fisch
 * File: BtsQueue.hpp
 * ******************************/

#pragma once
#include <queue>	/*std::priority_queue*/
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

//#define TEST uncomment inorder to see what happens when you don't lock

namespace ilrd
{

template<typename T, typename COMPARE = std::greater<T> >
class BtsQueue
{
public:
    BtsQueue() = default;
    void Enqueue(const T& task);
    void Dequeue(T& task);
	void Clear();
  
private:
    BtsQueue(const BtsQueue& other){};
    void operator=(const BtsQueue& other){};
	std::priority_queue<T, std::vector<T>, COMPARE> m_priqueue;
	std::mutex m_lock;
    std::condition_variable cond;

}; // class PriQueue

template <typename T, typename COMPARE>
inline void BtsQueue<T, COMPARE>::Enqueue(const T &task)
{
    std::unique_lock<std::mutex> lock(m_lock);
    m_priqueue.push(task);
    lock.unlock();
    cond.notify_one();
}

template <typename T, typename COMPARE>
inline void BtsQueue<T, COMPARE>::Dequeue(T &task)
{
    #ifndef TEST
    std::unique_lock<std::mutex> lock(m_lock);
    while (m_priqueue.empty())//allways check for emptyness after acquire the lock
    {
      cond.wait(lock);
    }
    task = m_priqueue.top();
    m_priqueue.pop();
    #endif

    #ifdef TEST
    while(!(m_priqueue.empty()))
    {
        task = m_priqueue.top();
        m_priqueue.pop();
    }
    #endif
}

template <typename T, typename COMPARE>
inline void BtsQueue<T, COMPARE>::Clear()
{
    std::unique_lock<std::mutex> lock(m_lock);
    while (!(m_priqueue.empty()))
    {
      m_priqueue.pop();
    }
}

} // ilrd