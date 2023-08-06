/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: scoped_lock.cpp
 * ******************************/

#include "scoped_lock.hpp"

namespace ilrd
{

ScopedLock::ScopedLock(pthread_mutex_t &mutex): m_lock(&mutex)
{
    // RAII lock: when aquireing a lock operarion it is done inside a constructor
    pthread_mutex_lock(m_lock); 
}

ScopedLock::~ScopedLock()
{
    // RAII lock: when releasing a lock operarion it is done inside a distructor
    pthread_mutex_unlock(m_lock); 
}
    
} // namespace ilrd
